#include "common/types.h"
#include "console/video_frame_buffer.h"

ssize_t write_screen(const char *str, size_t count)
{
  return vfb_write(str, count);
}
