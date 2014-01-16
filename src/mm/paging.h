#ifndef		PAGING_H_
# define	PAGING_H_

# include "common/types.h"

# define PAGE_SIZE	4096

typedef struct page
{
  uint32_t present    : 1;
  uint32_t writable   : 1;
  uint32_t user	      : 1;
  uint32_t pwt	      : 1;   /* ? */
  uint32_t pcd	      : 1;   /* ? */
  uint32_t accessed   : 1;   /* Has page been accessed? */
  uint32_t dirty      : 1;   /* Has page been written to? */
  uint32_t pat	      : 1;   /* PAT */
  uint32_t global     : 1;
  uint32_t unused     : 3;   /* Ignored */
  uint32_t frame      : 20;  /* Frame address */
} page_t;

typedef struct page_table
{
  page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
  page_table_t *tables[1024];
  uint32_t tablesPhysical[1024];
} page_directory_t;

void switch_page_directory(void *page);

#endif
