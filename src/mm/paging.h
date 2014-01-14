#ifndef		PAGING_H_
# define	PAGING_H_

# include "common/types.h"

# define PAGE_SIZE	4096

typedef struct page
{
  uint32_t present    : 1;   // Page present in memory
  uint32_t rw         : 1;   // Read-only if clear, readwrite if set
  uint32_t user       : 1;   // Supervisor level only if clear
  uint32_t accessed   : 1;   // Has page been accessed since last rfresh?
  uint32_t dirty      : 1;   // Has page been written to since last rfresh?
  uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
  uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
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
