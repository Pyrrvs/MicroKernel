#include "boot/gdt.h"
#include "common/stdio.h"

extern void gdt_load(void *ptr);

gdt_t gdt = {
  .ptr = {
    .limit = sizeof(gdt.table) - 1,
    .base = (uint32_t)gdt.table,
  },
  .table = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0xFF, 0xFF, 0, 0, 0, 0x9A, 0xCF, 0}, /* Ring 0 CS */
    { 0xFF, 0xFF, 0, 0, 0, 0x92, 0xCF, 0}, /* Ring 0 DS */
    { 0xFF, 0xFF, 0, 0, 0, 0xFA, 0xCB, 0}, /* Ring 3 CS */
    { 0xFF, 0xFF, 0, 0, 0, 0xF2, 0xCB, 0}, /* Ring 3 DS */
  }
};

void gdt_init(void)
{
  puts("Loading GDT\n");
  /* Load the GDT */
  gdt_load(&gdt.ptr);
  puts("GDT loaded\n");  
}
