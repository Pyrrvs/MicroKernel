#include "mm/paging.h"
#include "common/kernel.h"
#include "common/stdio.h"
#include "boot/isr.h"

/* Define it here for the moment */

page_directory_entry_t k_pagedir[1024] __attribute__((aligned(4096)));
page_table_t k_pagetable __attribute__((aligned(4096)));

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
  putunbr_base(faulting_address, HEX_BASE);
  puts("\n");
  PANIC("Page fault");
}

static void _init_page_table(void)
{
  page_t page;

  page.value = 0;
  page.present = 1;
  page.writable = 1;
  page.user = 1;
  for (int i = 0; i < 0x400000; i += PAGE_SIZE)
    {
      page.frame = i >> 12;
      k_pagetable.pages[i/PAGE_SIZE] = page; /* PRES/RW/USER. */ 
    }
  /* Making last page (0xC03FF000) RO for test purpose */
  /* k_pagetable.pages[1023].writable = 0; /\* PRES/RO/USER. *\/  */
  /* Making last page (0xC03FF000) system only for test purpose */
  k_pagetable.pages[1023].user = 0; /* PRES/RO/USER. */
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
    .table = ((uint32_t)&k_pagetable - KERNEL_VIRTUAL_BASE) >> 12
  };

  _init_page_table();
  k_pagedir[0].value = 0;
  k_pagedir[(KERNEL_VIRTUAL_BASE >> 22)] = entry;
  isr_register(0xE, kpaging_fault);
  switch_page_directory(((char*)&k_pagedir) - KERNEL_VIRTUAL_BASE);
  puts("Minimal paging initialized\n");
}
