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
    

  if (mboot_info->flags & MULTIBOOT_INFO_CMDLINE)
  {
    printk(INFO_COLOR "Command line: " DEF_COLOR
           "[%s]\n", mboot_info->cmdline + KERNEL_VIRTUAL_BASE);
  }
  

  if (mboot_info->flags & MULTIBOOT_INFO_MODS)
  {
    printk(INFO_COLOR "Modules info: " DEF_COLOR
           "count [%u]\n", mboot_info->mods_count);
      
    MODULES_FOREACH(mod, (mboot_info->mods_addr + KERNEL_VIRTUAL_BASE), mboot_info->mods_count)
    {
      printk("\tModule start at [%x] and ends at [%x] ; cmdline [%s]\n", \
             mod->mod_start, mod->mod_end, mod->cmdline + KERNEL_VIRTUAL_BASE);
    }
  }
  
  
  if (mboot_info->flags & MULTIBOOT_INFO_MEM_MAP)
  {
    printk(INFO_COLOR "Memory map: " DEF_COLOR
           "length [%u]\n", mboot_info->mmap_length);
            
    MMAP_FOREACH(ent, mboot_info->mmap_addr, mboot_info->mmap_length)
    {
      char *str;
      uint64_t len = ent->len;
      int i;
      for (i = 0, len = ent->len; i < 4 && len / 1024; len /= 1024)
        ++i;
      if (i == 0)
        str = "B";
      else if (i == 1)
        str = "KB";
      else if (i == 2)
        str = "MB";
      else
        str = "GB";
      printk("\tEntry: size [%u] ;  addr [%lx] ; len [%lu%s] ; type [%x]",
             ent->size, ent->addr, len, str, ent->type);
      if (ent->type & MULTIBOOT_MEMORY_AVAILABLE)
        printk(" ; available");
      if (ent->type & MULTIBOOT_MEMORY_RESERVED)
        printk(" ; reserved");
      printk("\n");
    }
  }

  g_mem_info.phys.total_size = mboot_info->mem_upper * 1024 + 1;
  g_mem_info.phys.higher_addr = mboot_info->mem_upper * 1024;
  printk(INFO_COLOR "Multiboot memory info:\n" DEF_COLOR);
  printk("\tmapping: lower [%x - %x] ; upper [%x - %x]\n",
         0,
         mboot_info->mem_lower * 1024 - 1,
         mboot_info->mem_lower * 1024,
         g_mem_info.phys.higher_addr - 1);
  printk("\tavailable size: lower %u KB ; upper %u MB ; total size %u MB\n",
         mboot_info->mem_lower,
         (mboot_info->mem_upper - mboot_info->mem_lower) / 1024,
         g_mem_info.phys.total_size / 1024 / 1024);

  printk("\tkernel_end PHYS %x\n", ALIGN_TO_PAGE(kernel_end_ptr));
  return 0;
}

