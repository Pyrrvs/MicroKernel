#include "3rdparty/multiboot.h"
#include "common/stdio.h"
#include "mm/mm.h"
#include "common/kernel.h"

mem_info_t g_mem_info;

extern char *kernel_end;
void *kernel_end_ptr = ((char *)&kernel_end) - KERNEL_VIRTUAL_BASE + sizeof(char*);

int mm_init(multiboot_info_t * mboot_info)
{

  if (mboot_info->flags & MULTIBOOT_INFO_MEMORY == 0)
  {
    PANIC("No memory information available in the multiboot structure\n");
  }

  /* if (mboot_info->flags & MULTIBOOT_INFO_CMDLINE) */
  /* { */
  /*   printk(INFO_COLOR "Command line: " DEF_COLOR */
  /*          "[%s]\n", mboot_info->cmdline + KERNEL_VIRTUAL_BASE); */
  /* } */


  /* if (mboot_info->flags & MULTIBOOT_INFO_MODS) */
  /* { */
  /*   printk(INFO_COLOR "Modules info: " DEF_COLOR */
  /*          "count [%u]\n", mboot_info->mods_count); */

  /*   MODULES_FOREACH(mod, (mboot_info->mods_addr + KERNEL_VIRTUAL_BASE), */
  /*                   mboot_info->mods_count) */
  /*   { */
  /*     printk("\tModule start at [%x] and ends at [%x] ; cmdline [%s]\n", \ */
  /*            mod->mod_start, mod->mod_end, mod->cmdline + KERNEL_VIRTUAL_BASE); */
  /*   } */
  /* } */

  g_mem_info.phys.heap.start_addr = (uint32_t)ALIGN_TO_PAGE(kernel_end_ptr);

  if (mboot_info->flags & MULTIBOOT_INFO_MEM_MAP)
  {
    printk(INFO_COLOR "Memory map: " DEF_COLOR
           "length [%u]\n", mboot_info->mmap_length);

    MMAP_FOREACH(ent, mboot_info->mmap_addr, mboot_info->mmap_length)
    {
      if (ent->addr >  g_mem_info.phys.heap.start_addr
          && ent->type & MULTIBOOT_MEMORY_RESERVED)
      {
        g_mem_info.phys.heap.end_addr = ent->addr - 1;
        break ;
      }
    }
  }
  printk("\theap_start PHYS %x\n", g_mem_info.phys.heap.start_addr);
  printk("\theap_end PHYS %x\n", g_mem_info.phys.heap.end_addr);

  g_mem_info.phys.total_size = mboot_info->mem_upper * 1024 + 1;
  g_mem_info.phys.higher_addr = mboot_info->mem_upper * 1024;

  //_init_heap();


  /* printk(INFO_COLOR "Multiboot memory info:\n" DEF_COLOR); */
  /* printk("\tmapping: lower [%x - %x] ; upper [%x - %x]\n", */
  /*        0, */
  /*        mboot_info->mem_lower * 1024 - 1, */
  /*        mboot_info->mem_lower * 1024, */
  /*        g_mem_info.phys.higher_addr - 1); */
  /* printk("\tavailable size: lower %u KB ; upper %u MB ; total size %u MB\n", */
  /*        mboot_info->mem_lower, */
  /*        (mboot_info->mem_upper - mboot_info->mem_lower) / 1024, */
  /*        g_mem_info.phys.total_size / 1024 / 1024); */
  return 0;
}

