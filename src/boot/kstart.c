#include "common/stdio.h"
#include "common/kernel.h"
#include "mm/mm.h"
#include "3rdparty/multiboot.h"
#include "boot/isr.h"
#include "process/services.h"

extern char *services_start;
extern char *services_end;

void gp_handler(registers_t *regs)
{
  PANIC("General Protection Fault\n");
}

int kstart(int code, multiboot_info_t * mboot_info)
{
  isr_register(0xD, gp_handler);
  if (code != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    PANIC("Kernel need to be loaded by a multiboot"
	" compliant bootloader\n");
  }
  printk("Kernel up and running\n");
  // printk("Size of unsigned long long %d\n", sizeof(unsigned long long));
  // mm_init(mboot_info);


  printk("Services start %x\n", &services_start);
  printk("Services end %x\n", &services_end);
  services_init(mboot_info);
  return 0xDEAD;
}
