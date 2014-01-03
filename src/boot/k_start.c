#include "console/video_frame_buffer.h"
#include "common/stdio.h"

int k_start(void)
{
  vfb_clear();
  puts("#toto");
  return 0xBABA;
}
