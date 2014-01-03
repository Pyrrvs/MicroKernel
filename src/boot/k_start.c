#include "console/video_frame_buffer.h"

int k_start(void)
{
  vfb_clear();
  vfb_putc('#');
  return 0xBABA;
}
