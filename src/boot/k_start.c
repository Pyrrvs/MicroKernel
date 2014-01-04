#include "console/video_frame_buffer.h"
#include "common/stdio.h"

int k_start(void)
{
  vfb_clear();
  char *str = "titi";
  putnbr((int)str);
  printk("#toto %s", str);
  return 0xBABA;
}
