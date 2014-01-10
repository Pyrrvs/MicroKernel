#ifndef		GDT_H_
# define	GDT_H_

# include "common/types.h"

/* GDT Descr */
struct gdt_descr
{
  uint16_t limit_low;
  uint16_t base_low; 
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} __attribute__((packed));
typedef struct gdt_descr gdt_descr_t;

struct gdt
{
  /* GDT Pointer */
  struct {
    uint16_t limit;
    uint32_t base;
  } __attribute__((packed)) ptr;
  /* GDT descriptors*/
  gdt_descr_t table[5];
} __attribute__((packed));
typedef struct gdt gdt_t;

/* Init GDT */
void gdt_init(void);

#endif
