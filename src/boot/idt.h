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
void idt_load(void *ptr);
void idt_init(void);

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

#endif
