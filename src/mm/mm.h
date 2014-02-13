#ifndef		MM_H_
# define	MM_H_

# include "common/types.h"
# include "3rdparty/multiboot.h"

# define PAGE_AVAILABLE 0
# define PAGE_USED 1
# define MARK_AVAILABLE(PAGE) (g_mem_info.phys.heap.page_bf[PAGE / 32] &= \
                               ~(1 << (PAGE % 32)))
# define MARK_USED(PAGE) (g_mem_info.phys.heap.page_bf[PAGE / 32] |= \
                          (1 << (PAGE % 32)))

# define PAGE_STATE(PAGE) (g_mem_info.phys.heap.page_bf[PAGE / 32] & (1 << (PAGE % 32))) \
  >> (PAGE % 32)

typedef struct mem_info
{
  struct {
    uint32_t total_size;
    uint32_t higher_addr;
    struct {
      uint32_t start_addr;
      uint32_t end_addr;
      uint32_t *page_bf; /* Page state bitfield */
      uint32_t nb_pages;
    } heap;
  } phys;
} mem_info_t;

extern mem_info_t g_mem_info;
int mm_init(multiboot_info_t * mboot_info);

#endif
