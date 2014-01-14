#include "boot/isr.h"
#include "common/stdio.h"
#include "common/kernel.h"

static isr_t isrs[256];

void isr_handler(registers_t regs)
{
  puts(INFO_COLOR "interrupt handler\n" DEF_COLOR);
  puts("Interrupt number: ");
  putnbr(regs.int_no);
  putc('\n');
  if (regs.err_code)
    {
      puts("Error code: ");
      putnbr(regs.err_code);
      putc('\n');
    }
  if (regs.int_no == 0xD)
    {
      PANIC("Fuck that shit! I'm out of here!\n");
    }
  else if (regs.int_no == 0xE)
    {
      uint32_t faulting_address;
      asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

      int present   = !(regs.err_code & 0x1); // Page not present
      int rw = regs.err_code & 0x2;           // Write operation?
      int us = regs.err_code & 0x4;           // Processor was in user-mode?
      int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
      int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

      // Output an error message.
      puts("Page fault! ( ");
      if (present) {puts("present ");}
      if (rw) {puts("read-only ");}
      if (us) {puts("user-mode ");}
      if (reserved) {puts("reserved ");}
      puts(") at 0x");
      putnbr(faulting_address);
      puts("\n");
      PANIC("Page fault");
    }
}
