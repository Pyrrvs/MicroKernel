#include "console/video_frame_buffer.h"
#include "common/stdio.h"

int k_start(void)
{
  vfb_clear();
  printk("Kernel down and running");
  printk("\rKernel up and running  \n");
  printk("#toto %d\n", 42);
  return 0xBABA;
}
