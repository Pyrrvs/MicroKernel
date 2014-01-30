#ifndef		ISR_H_
# define	ISR_H_

# include "common/types.h"

/* Keep it organized that way. Order matters. */
typedef struct registers
{
  uint32_t	ds;
  uint32_t	edi;
  uint32_t	esi;
  uint32_t	ebp;
  uint32_t	esp;
  uint32_t	ebx;
  uint32_t	edx;
  uint32_t	ecx;
  uint32_t	eax;
  uint32_t	int_no;
  uint32_t	err_code;
  uint32_t	eip;
  uint32_t	cs;
  uint32_t	eflags;
  uint32_t	useresp;
  uint32_t	ss;
} registers_t;

typedef void (*isr_t)(registers_t *regs);
void isr_register(uint8_t num, isr_t handler);
void isr_unregister(uint8_t num);
void isr_handler(registers_t regs);

#endif
