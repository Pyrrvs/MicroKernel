#include "console/video_frame_buffer.h"
#include "common/stdio.h"

int k_start(void)
{
  vfb_clear();
  printk("Kernel down and running");
  printk("\rKernel up and running  \n");
  printk("\x1B[42;31mtest\x1B[37;40m\n");
  printk("\x1B[1;42;31mtest\x1B[0;37;40m\n");
  printk("#toto %d\n", 42);
  puts("\x1B[41;32mtest\x1B[37;40m\n");
  puts("\x1B[41;32;1mtest\x1B[37;40;0m\n");
  puts("no way!\n");
  return 0xBABA;
}
