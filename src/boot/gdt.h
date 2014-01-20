#ifndef		GDT_H_
# define	GDT_H_

# include <common/types.h>

struct tss {
  uint16_t prevlink, plh;
  uint32_t esp0; // KERNEL STACK
  uint16_t ss0, ss0h; // KERNEL SS (0x10)
  uint32_t esp1;
  uint16_t ss1, ss1h;
  uint32_t esp2;
  uint16_t ss2, ss2h;
  uint32_t cr3, eip, eflags;
  uint32_t eax,ecx,edx,ebx,esp,ebp,esi,edi;
  uint16_t es, esh;
  uint16_t cs, csh;
  uint16_t ss, ssh;
  uint16_t ds, dsh;
  uint16_t fs, fsh;
  uint16_t gs, gsh;
  uint16_t ldt, ldth;
  uint16_t iomapbl, iomapbase;
} __attribute__((packed));
typedef struct tss tss_t;

typedef struct 
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

#endif
