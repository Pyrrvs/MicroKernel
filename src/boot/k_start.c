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

  printk(WARN_COLOR "Testing interrupts\n" DEF_COLOR);
  asm volatile ("int $0x0");
  asm volatile ("int $0x3");

  printk(WARN_COLOR
	 "Testing pagination (accessing memory higher than 0xC0000000)\n"
	 DEF_COLOR);
  char *str = "This string is located somewhere below 0x400000\n";
  str += 0xC0000000;
  puts(str);

  printk(WARN_COLOR
	 "Testing page fault (accessing 0x400001)\n"
	 DEF_COLOR);
  str = (char*)0x400001;
  putc(str[0]);
  return 0xBABA;
}
