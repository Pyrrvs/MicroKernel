#include "console/video_frame_buffer.h"
#include "common/stdio.h"

int k_start(void)
{
  vfb_clear();
  printk("#toto");
  return 0xBABA;
}
