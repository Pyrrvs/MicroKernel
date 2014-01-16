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

  int present   = !(regs->err_code & 0x1);
  int rw = regs->err_code & 0x2;
  int us = regs->err_code & 0x4;
  int reserved = regs->err_code & 0x8;
  int id = regs->err_code & 0x10;

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

static void _init_page_table(void)
{
  page_t page;

  page.present = 1;
  page.writable = 1;
  page.user = 1;
  for (int i = 0; i < 0x400000; i += PAGE_SIZE)
    {
      page.frame = i >> 12;
      k_pagetable.pages[i/PAGE_SIZE] = page; /* PRES/RW/USER. */ 
    }
  /* Making last page (0xC03FF000) RO for test purpose */
  k_pagetable.pages[1023].writable = 0; /* PRES/RO/USER. */ 
}

void kpaging_init(void)
{
  page_directory_entry_t entry = {
    .present = 1,
    .writable = 1,
    .user = 1,
    .pwt = 0,
    .pcd = 0,
    .accessed = 0,
    .unused = 0,
    .table = (uint32_t)&k_pagetable >> 12
  };

  _init_page_table();
  k_pagedir.tables[0] = &k_pagetable;
  k_pagedir.entries[0] = entry;
  k_pagedir.tables[((KERNEL_ADDR >> 22) & 0x3FF)] = &k_pagetable;
  k_pagedir.entries[((KERNEL_ADDR >> 22) & 0x3FF)] = entry;
  isr_register(0xE, kpaging_fault);
  switch_page_directory(&k_pagedir.entries);
  puts("Minimal paging initialized\n");
}
