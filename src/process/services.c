#include "common/kernel.h"
#include "3rdparty/multiboot.h"

void services_init(multiboot_info_t *mboot_info)
{
  if (mboot_info->flags & MULTIBOOT_INFO_CMDLINE)
  {
    printk(INFO_COLOR "Command line: " DEF_COLOR
        "[%s]\n", mboot_info->cmdline + KERNEL_VIRTUAL_BASE);
  }


  if (mboot_info->flags & MULTIBOOT_INFO_MODS)
  {
    printk(INFO_COLOR "Modules info: " DEF_COLOR
        "count [%u]\n", mboot_info->mods_count);

    MODULES_FOREACH(mod, (mboot_info->mods_addr + KERNEL_VIRTUAL_BASE),
        mboot_info->mods_count)
    {
      printk("\tModule start at [%x] and ends at [%x] ; cmdline [%s]\n", \
          mod->mod_start, mod->mod_end, mod->cmdline + KERNEL_VIRTUAL_BASE);

          //_load_elf(mod);

          printk("MAGIC: %x\n", *((char *)mod->mod_start + KERNEL_VIRTUAL_BASE));
    }
  }
}
