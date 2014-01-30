#ifndef		PAGING_H_
# define	PAGING_H_

# include "common/types.h"

# define PAGE_SIZE	4096

typedef union {
  uint32_t value;
  struct
  {
    uint32_t present    : 1;
    uint32_t writable   : 1;
    uint32_t user       : 1;
    uint32_t pwt        : 1;   /* ? */
    uint32_t pcd        : 1;   /* ? */
    uint32_t accessed   : 1;   /* Has page been accessed? */
    uint32_t dirty      : 1;   /* Has page been written to? */
    uint32_t pat        : 1;   /* PAT */
    uint32_t global     : 1;
    uint32_t unused     : 3;   /* Ignored */
    uint32_t frame      : 20;  /* Frame address */
  };
} page_t;

typedef struct page_table
{
  page_t pages[1024];
} page_table_t;

typedef union
{
  uint32_t value;
  struct
  {
    uint32_t present    : 1;
    uint32_t writable   : 1;
    uint32_t user       : 1;
    uint32_t pwt        : 1;   /* ? */
    uint32_t pcd        : 1;   /* ? */
    uint32_t accessed   : 1;   /* Has page been accessed? */
    uint32_t unused     : 6;   /* Ignored */
    uint32_t table      : 20;  /* Page Table Address */
  };
} page_directory_entry_t;

typedef struct page_directory
{
} page_directory_t;

void switch_page_directory(void *page);

#endif
