#include "boot/isr.h"
#include "common/stdio.h"
#include "common/kernel.h"

static isr_t handlers[256];

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
  if (handlers[regs.int_no])
    handlers[regs.int_no](&regs);
  else
    PANIC("Unhandled interruption\n");
}

void isr_register(uint8_t num, isr_t handler)
{
  handlers[num] = handler;
}

void isr_unregister(uint8_t num)
{
  handlers[num] = NULL;
}
