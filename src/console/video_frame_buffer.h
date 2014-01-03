#ifndef		VID_FRAME_BUFFER_H_
# define	VID_FRAME_BUFFER_H_

# include "common/types.h"

# define VID_FRAME_BUF (void*)0xB8000
# define NB_LINE 25
# define NB_COL 80

struct s_vfb {
  struct {
    int x;
    int y;
  } pos;
  uint8_t color;
  uint16_t *base;
};

void vfb_putc(char c);
void vfb_puts(char *s);
void vfb_putnbr(int nbr);
void vfb_putnbr_base(int nbr, char *base);
void vfb_set_color(uint8_t color);
void vfb_set_backgrd_color(uint8_t color);
void vfb_set_foregrd_color(uint8_t color);
void vfb_clear(void);
#endif