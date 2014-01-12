#ifndef		IDT_H_
# define	IDT_H_

# include "common/types.h"

struct idt_entry {
  uint16_t isr_addr_low;
  uint16_t target_segment;
  uint8_t zero;
  uint8_t flags;
  uint16_t isr_addr_high;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt {
  /* IDT Pointer */
  struct {
    uint16_t limit;
    uint32_t base;
  } __attribute__((packed)) ptr;
  idt_entry_t table[256];
} __attribute__((packed));
typedef struct idt idt_t;

void idt_set_entry(uint8_t num, uint32_t isr_addr,
		   uint16_t target_segment, uint8_t flags);
void idt_load(void);
void idt_init(void);

#endif
