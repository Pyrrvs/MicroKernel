#include "console/video_frame_buffer.h"
#include "common/stdio.h"
#include "common/kernel.h"
#include "3rdparty/multiboot.h"

int k_start(int code, multiboot_info_t * mBootInfo)
{
  if (code != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      PANIC("Kernel need to be loaded by a multiboot"
	    " compliant bootloader\n");
    }
  printk("Kernel up and running\n");
  asm volatile ("int $0x0");
  asm volatile ("int $0x3");
  /* printk(WARN_COLOR "Next interruption will cause a panic\n" DEF_COLOR); */
  /* asm volatile ("int $0x20"); */
  printk("still alive\n");
  return 0xBABA;
}
