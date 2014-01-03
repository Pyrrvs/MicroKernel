#ifndef		CONSOLE_H_
# define	CONSOLE_H_

# include "common/types.h"

# define VID_FRAME_BUF 0xB8000

struct s_console {
  struct {
    int x;
    int y;
  } pos;
  union {
    uint8_t color;
    uint8_t backgrd : 4;
    uint8_t foregrd : 4;
  } color;
};

void console_putc(char c);
void console_puts(char *s);
void console_putnbr(int nbr);
void console_putnbr_base(int nbr, char *base);
void console_set_color(uint8_t color);
void console_set_backgrd_color(uint8_t color);
void console_set_foregrd_color(uint8_t color);

#endif
