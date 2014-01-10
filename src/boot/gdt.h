#ifndef		GDT_H_
# define	GDT_H_

# include "common/types.h"

struct gdt
{
  /* GDT Pointer */
  struct {
    uint16_t limit;
    uint32_t base;
  } __attribute__((packed)) ptr;
  /* GDT descriptors*/
  uint8_t table[5][8];
} __attribute__((packed));
typedef struct gdt gdt_t;

/* Init GDT */
void gdt_init(void);

#endif
