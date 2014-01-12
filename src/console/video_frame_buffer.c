#include "common/stdio.h"
#include "common/string.h"
#include "common/stdlib.h"
#include "io/lowlevel_io.h"
#include "console/video_frame_buffer.h"

/* Make it thread safe when synch mechanism available */
static struct s_vfb g_vfb = {
  .pos = { .x = 0, .y = 0},
  .color = 0x07,
  .base = VID_FRAME_BUF,
  .is_esc_seq = 0,
  .esc_buf_ndx = 0,
};

int vfb_foregrd_val[] = {
  0x00, /* 30 - black	- #000000 */
  0x04, /* 31 - red	- #FF0000 */
  0x02, /* 32 - green	- #00FF00 */
  0x06, /* 33 - yellow	- #FFFF00 */
  0x01, /* 34 - blue	- #0000FF */
  0x05, /* 35 - magenta	- #FF00FF */
  0x03, /* 36 - cyan	- #00FFFF */
  0x07, /* 37 - white	- #FFFFFF */
};

int vfb_backgrd_val[] = {
  0x00, /* 40 - black	- #000000 */
  0x40, /* 41 - red	- #FF0000 */
  0x20, /* 42 - green	- #00FF00 */
  0x60, /* 43 - yellow	- #FFFF00 */
  0x10, /* 44 - blue	- #0000FF */
  0x50, /* 45 - magenta	- #FF00FF */
  0x30, /* 46 - cyan	- #00FFFF */
  0x70, /* 47 - white	- #FFFFFF */
};

static inline void _handle_color_code(int color)
{
  if (color >= 0 && color <= 8)
    {
      if (color == 0)
	g_vfb.color &= 0x77;
      if (color == 1)
	g_vfb.color |= 0x88;
    }
  else if (color >= 30 && color <= 37)
    {
      g_vfb.color = (g_vfb.color & 0x78) | (vfb_foregrd_val[color - 30] & 0x7);
    }
  else if (color >= 40 && color <= 47)
    {
      g_vfb.color = (vfb_backgrd_val[color - 40] & 0x70) | (g_vfb.color & 0x8F);
    }
}

static inline char _handle_color_seq(void)
{
  char *str = g_vfb.esc_buf;
  int codes[3] = { 0, 0, 0 };

  int i = 1, j = 0;
  for (char stop = 0; !stop; ++j)
    {
      if (j >= 3)
	return 0;
      codes[j] = atoi(str + i);
      while (i < g_vfb.esc_buf_ndx && str[i] != ';' && str[i] != 'm')
	++i;
      if (i >= g_vfb.esc_buf_ndx)
	return 0;
      else if (str[i] == 'm')
	stop = 1;
      else if (str[i] == ';')
	++i;
    }
  for (i = 0; i < j; ++i)
    _handle_color_code(codes[i]);
  return 1;
}

static inline char _handle_escape_seq()
{
  char status = 0;
  
  /* Color sequence */
  if (g_vfb.esc_buf[0] == '[')
    status = _handle_color_seq();
  return status;
}

static inline void _carriage_return(void)
{
  g_vfb.pos.x = 0;
}

static inline void _back_cursor(void)
{
  if (g_vfb.pos.x > 0)
    --g_vfb.pos.x;
}

static inline void _scroll_up(void)
{
  for (int i = 0; i < NB_LINE*NB_COL; ++i)
    {
      if (i < (NB_LINE - 1) * 80)
	g_vfb.base[i] = g_vfb.base[i + NB_COL];
      else
	g_vfb.base[i] = ' ' | (((0 << 4) | (15 & 0x0F)) << 8);
    }
  g_vfb.pos.y = NB_LINE - 1;
  g_vfb.pos.x = 0;
}

static inline void _add_newline(void)
{
  g_vfb.pos.x = 0;
  if (g_vfb.pos.y < NB_LINE - 1)
    ++g_vfb.pos.y;
  else
    _scroll_up();
}

static inline void _putc(char c)
{
  g_vfb.base[g_vfb.pos.y * NB_COL + g_vfb.pos.x] = (g_vfb.color << 8) | c;
  if (++g_vfb.pos.x == NB_COL)
    _add_newline();
}

ssize_t vfb_write(const char *str, size_t count)
{
  ssize_t i;
  for (i = 0; i < (ssize_t)count; ++i)
    if (g_vfb.is_esc_seq)
      {
	g_vfb.esc_buf[g_vfb.esc_buf_ndx++] = str[i];
	if (_handle_escape_seq())
	  {
	    g_vfb.is_esc_seq = 0;
	    g_vfb.esc_buf_ndx = 0;
	  }
     }
    else if (str[i] == 27)
      g_vfb.is_esc_seq = 1;
    else if (str[i] == '\n')
      _add_newline();
    else if (str[i] == '\b')
      _back_cursor();
    else if (str[i] == '\r')
      _carriage_return();
    else
      _putc(str[i]);
  return i;
}

void vfb_clear(void)
{
  memset(g_vfb.base, 0, NB_COL * NB_LINE * 2);
  g_vfb.pos.x = 0;
  g_vfb.pos.y = 0;
}
