#include "mm/paging.h"
#include "common/kernel.h"
#include "common/stdio.h"
#include "boot/isr.h"

/* Define it here for the moment */
# define KERNEL_ADDR 0xC0000000

page_directory_t k_pagedir __attribute__((aligned(4096))) __attribute__((section("kpages")));
page_table_t k_pagetable __attribute__((aligned(4096))) __attribute__((section("kpages")));

void kpaging_fault(registers_t *regs)
{
  uint32_t faulting_address;
  asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

  int present   = !(regs->err_code & 0x1); // Page not present
  int rw = regs->err_code & 0x2;           // Write operation?
  int us = regs->err_code & 0x4;           // Processor was in user-mode?
  int reserved = regs->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
  int id = regs->err_code & 0x10;          // Caused by an instruction fetch?

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

void kpaging_init(void)
{
  page_t page;

  page.present = 1;
  page.rw = 1;
  page.user = 1;
  for (int i = 0; i < 0x400000; i += PAGE_SIZE)
    {
      page.frame = i >> 12;
      k_pagetable.pages[i/PAGE_SIZE] = page; /* PRES/RO/KERN. */ 
    }

  k_pagedir.tables[0] = &k_pagetable;
  /* PRST/RW/US */
  k_pagedir.tablesPhysical[0] = ((uint32_t)&k_pagetable) | 0x7;

  k_pagedir.tables[((KERNEL_ADDR >> 22) & 0x3FF)] = &k_pagetable;
  /* PRST/RW/US */
  k_pagedir.tablesPhysical[((KERNEL_ADDR >> 22) & 0x3FF)] = ((uint32_t)&k_pagetable) | 0x7;

  isr_register(0xE, kpaging_fault);
  switch_page_directory(&k_pagedir.tablesPhysical);
  puts("Minimal paging initialized\n");
}
