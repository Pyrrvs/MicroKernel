#include "console/video_frame_buffer.h"
#include "common/stdio.h"
#include "common/kernel.h"
#include "3rdparty/multiboot.h"
#include "boot/isr.h"

void gp_handler(registers_t *regs)
{
  PANIC("Fuck that shit! I'm out of here!\n");
}

int k_start(int code, multiboot_info_t * mBootInfo)
{
  if (code != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      PANIC("Kernel need to be loaded by a multiboot"
	    " compliant bootloader\n");
    }
  printk("Kernel up and running\n");

  isr_register(0xD, gp_handler);
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
	 "Testing pagination (writing in memory higher than 0xC0000000)\n"
	 DEF_COLOR);
  str[5] = '$';
  puts(str);


  printk(WARN_COLOR
	 "Testing page fault (accessing 0x400001)\n"
	 DEF_COLOR);
  str = (char*)0x400001;
  putc(str[0]);
  return 0xBABA;
}
