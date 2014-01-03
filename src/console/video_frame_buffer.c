#include "common/string.h"
#include "io/lowlevel_io.h"
#include "console/video_frame_buffer.h"

// Make it thread safe when synch mechanism available
static struct s_vfb g_vfb = {
  .pos = { .x = 0, .y = 0},
  .color = 0x14,
  .base = VID_FRAME_BUF,
};

void vfb_putc(char c)
{
  g_vfb.base[g_vfb.pos.y * NB_COL + g_vfb.pos.x] = (g_vfb.color << 8) | c;
}

void vfb_putnbr(int nbr)
{
  if (nbr < 0)
    {
      vfb_putc('-');
      vfb_putnbr(nbr / -10);
      vfb_putc(-(nbr % 10) + '0');
    }
  else
    {
      if (nbr > 10)
	vfb_putnbr(nbr / 10);
      vfb_putc((nbr % 10) + '0');      
    }
}

void vfb_clear(void)
{
  memset(g_vfb.base, 0, NB_COL * NB_LINE * 2);
}
