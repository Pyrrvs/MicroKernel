#include "console/video_frame_buffer.h"
#include "common/stdio.h"
#include "common/kernel.h"
#include "3rdparty/multiboot.h"
#include "boot/isr.h"

void test_handler(registers_t *regs)
{
  puts(SUCC_COLOR "Called from userland\n" DEF_COLOR);
  char *str = (char*)0xC03FF000;
  str[0] = '$';
  puts("gasd\n");
}

void gp_handler(registers_t *regs)
{
  PANIC("General Protection Fault\n");
}

int kstart(int code, multiboot_info_t * mBootInfo)
{
  printk("\n\n [ %s ]  = %d \n\n", "La vie L'univers et tout le reste", 42);

  if (code != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    PANIC("Kernel need to be loaded by a multiboot"
	" compliant bootloader\n");
  }

  printk("Kernel up and running\n");

  isr_register(0xD, gp_handler);

  printk(WARN_COLOR "Testing context switch\n" DEF_COLOR);
  isr_register(0x80, test_handler);
  test_switch();
  isr_unregister(0x80);

  return 0xBABA;
}
