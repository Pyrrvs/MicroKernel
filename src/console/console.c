#include "io/lowlevel_io.h"
#include "console/console.h"

// Make it thread safe when synch mechanism available
static struct s_console g_console;

void console_putc(char c)
{
  uint8_t test = (0 << 4) | (15 & 0x0F);
  /* uint16_t test2 = (test << 8) | c; */
  /* outw(test2, VID_FRAME_BUF); */
  char* video_mem = (void*)0xb8000;
  video_mem[(0 * 80 + 11) * 2] = 'k';
  video_mem[(0 * 80 + 11) * 2 + 1] = 0x14;
}

void console_putnbr(int nbr)
{
  if (nbr < 0)
    {
      console_putc('-');
      console_putnbr(nbr / -10);
      console_putc(-(nbr % 10) + '0');
    }
  else
    {
      if (nbr > 10)
	console_putnbr(nbr / 10);
      console_putc((nbr % 10) + '0');      
    }
}
