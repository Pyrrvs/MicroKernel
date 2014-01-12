#include "boot/isr.h"
#include "boot/idt.h"
#include "common/string.h"
#include "common/stdio.h"

isr_ptr isr_table[32];

static idt_t idt = {
  .ptr = {
    .base = (uint32_t)idt.table,
    .limit = sizeof(idt.table) - 1,
  },
};

void idt_set_entry(uint8_t num,
		   uint32_t isr_addr,
		   uint16_t target_segment,
		   uint8_t flags)
{
  idt.table[num].isr_addr_low = isr_addr & 0xFFFF;
  idt.table[num].isr_addr_high = (isr_addr >> 16) & 0xFFFF;

  idt.table[num].target_segment = target_segment;
  idt.table[num].zero = 0;

  idt.table[num].flags = flags /* | 0x60 or userland*/;
}

void idt_init(void)
{
  puts("Initializing IDT\n");
  memset((void*)idt.table, 0, sizeof(idt.table));
  for (uint8_t i = 0; i < (sizeof(isr_table) / sizeof(*isr_table)); ++i)
    idt_set_entry(i, (uint32_t)isr_table[i], 0x08, 0x8E);
  idt_load(&idt.ptr);
  puts("IDT initialized\n");
}
