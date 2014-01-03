#include "lowlevel_io.h"

void outb(uint8_t val, uint16_t port)
{
  /* asm volatile ("outb %0, %1":: "a" (val), "Nd" (port)); */
}

void outw(uint8_t val, uint16_t port)
{
  /* asm volatile ("outw %0, %1":: "a" (val), "Nd" (port)); */
}

void outd(uint8_t val, uint16_t port)
{
  /* asm volatile ("outd %0, %1":: "a" (val), "Nd" (port)); */
}

uint8_t inb(uint16_t port)
{
  int val;
  /* asm volatile ("inb %1, %0": "=a" (val), "Nd" (port)); */
  return val;
}

uint16_t inw(uint16_t port)
{
  int val;
  /* asm volatile ("inw %1, %0": "=a" (val), "Nd" (port)); */
  return val;
}

uint32_t ind(uint16_t port)
{
  int val;
  /* asm volatile ("ind %1, %0": "=a" (val), "Nd" (port)); */
  return val;
}
