#include "console/video_frame_buffer.h"
#include "common/stdio.h"
#include "common/kernel.h"
#include "3rdparty/multiboot.h"

int k_start(int code, multiboot_info_t * mBootInfo)
{
  vfb_clear();
  if (code != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      PANIC("Kernel need to be loaded by a multiboot"
	    " compliant bootloader\n");
    }
  printk("Kernel up and running");
  /* printk("\x1B[42;31mtest\x1B[37;40m\n"); */
  /* printk("\x1B[1;42;31mtest\x1B[0;37;40m\n"); */
  /* printk("#toto %d\n", 42); */
  /* puts("\x1B[41;32mtest\x1B[37;40m\n"); */
  /* puts("\x1B[41;32;1mtest\x1B[37;40;0m\n"); */
  /* puts("no way!\n"); */
  return 0xBABA;
}
