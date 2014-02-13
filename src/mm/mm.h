#ifndef		MM_H_
# define	MM_H_

# include "common/types.h"
# include "3rdparty/multiboot.h"

typedef struct mem_info
{
  struct {
    uint32_t total_size;
    uint32_t higher_addr;
    struct {
      uint32_t start_addr;
      uint32_t end_addr;
      uint32_t *frames;
    } heap;
  } phys;
} mem_info_t;

extern mem_info_t g_mem_info;
int mm_init(multiboot_info_t * mboot_info);

#endif
