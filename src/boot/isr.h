#ifndef		ISR_H_
# define	ISR_H_

# include "common/types.h"

typedef struct registers
{
  /* Data segment selector */
  uint32_t	ds;
  /* Pushed by pusha */
  uint32_t	edi;
  uint32_t	esi;
  uint32_t	ebp;
  uint32_t	esp;
  uint32_t	ebx;
  uint32_t	edx;
  uint32_t	ecx;
  uint32_t	eax;
  /* Interrupt number and error code (if applicable) */
  uint32_t	int_no;
  uint32_t	err_code;
  /* Pushed by the processor automatically. */
  uint32_t	eip;
  uint32_t	cs;
  uint32_t	eflags;
  uint32_t	useresp;
  uint32_t	ss;
} registers_t;

void isr_handler();

typedef void (*isr_ptr)(void);

void isr0(void);
void isr1(void);
void isr2(void);
void isr3(void);
void isr4(void);
void isr5(void);
void isr6(void);
void isr7(void);
void isr8(void);
void isr9(void);
void isr10(void);
void isr11(void);
void isr12(void);
void isr13(void);
void isr14(void);
void isr15(void);
void isr16(void);
void isr17(void);
void isr18(void);
void isr19(void);
void isr20(void);
void isr21(void);
void isr22(void);
void isr23(void);
void isr24(void);
void isr25(void);
void isr26(void);
void isr27(void);
void isr28(void);
void isr29(void);
void isr30(void);
void isr31(void);

#endif
