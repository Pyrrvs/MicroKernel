#include "common/stdio.h"
#include "common/kernel.h"
#include "3rdparty/multiboot.h"
#include "boot/isr.h"

void gp_handler(registers_t *regs)
{
  PANIC("General Protection Fault\n");
}

int kstart(int code, multiboot_info_t * mBootInfo)
{
  isr_register(0xD, gp_handler);
  if (code != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    PANIC("Kernel need to be loaded by a multiboot"
	" compliant bootloader\n");
  }
  printk("Kernel up and running\n");
  printk("%x\n", 42);

  return 0xDEAD;
}
