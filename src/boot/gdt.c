#include "boot/gdt.h"
#include "common/stdio.h"

extern void gdt_load(void *ptr);

gdt_t gdt;

static void gdt_add_descr(int8_t ndx, uint32_t base, uint32_t limit,
			  uint8_t access, uint8_t gran)
{
  gdt.table[ndx].base_low    = (base & 0xFFFF);
  gdt.table[ndx].base_middle = (base >> 16) & 0xFF;
  gdt.table[ndx].base_high   = (base >> 24) & 0xFF;
  gdt.table[ndx].limit_low   = (limit & 0xFFFF);
  gdt.table[ndx].granularity = (limit >> 16) & 0x0F;
  gdt.table[ndx].granularity |= gran & 0xF0;
  gdt.table[ndx].access      = access;
}

void gdt_init(void)
{
  puts("Loading GDT\n");
  /* Add segment descriptors to GDT */
  gdt_add_descr(0, 0, 0, 0, 0);
  gdt_add_descr(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Ring 0 CS
  gdt_add_descr(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Ring 0 DS
  gdt_add_descr(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Ring 3 CS
  gdt_add_descr(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Ring 3 DS

  /* Set GDT pointer*/
  gdt.ptr.limit = sizeof(gdt.table) - 1;
  gdt.ptr.base = (uint32_t)gdt.table;

  /* Load the GDT */
  gdt_load(&gdt.ptr);
  puts("GDT loaded\n");  
}
