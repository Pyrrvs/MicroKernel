#include "common/string.h"
#include "io/lowlevel_io.h"
#include "console/video_frame_buffer.h"

/* Make it thread safe when synch mechanism available */
static struct s_vfb g_vfb = {
  .pos = { .x = 0, .y = 0},
  .color = 0x0F,
  .base = VID_FRAME_BUF,
};

static inline int _handle_escape_seq(const char * str, size_t i, size_t count)
{
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

static inline void _add_newline(void)
{
  g_vfb.pos.x = 0;
  ++g_vfb.pos.y;
}

static inline void _putc(char c)
{
  g_vfb.base[g_vfb.pos.y * NB_COL + g_vfb.pos.x++] = (g_vfb.color << 8) | c;
  if (g_vfb.pos.x == NB_COL)
    _add_newline();
}

ssize_t vfb_write(const char *str, size_t count)
{
  ssize_t i;
  for (i = 0; i < (ssize_t)count; ++i)
    if (str[i] == 27)
      i += _handle_escape_seq(str, i, count);
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
