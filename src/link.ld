ENTRY(k_asm_entry)
OUTPUT_FORMAT(elf32-i386)
SECTIONS
{
    /* The kernel will live at 3GB + 1MB in the virtual
      address space, which will be mapped to 1MB in the
      physical address space. */
    . = 0xC0100000;

    .text ALIGN(0x1000) : AT(ADDR(.text) - 0xC0000000)
    {
        *(.text)
    }

    .rodata ALIGN(0x1000) : AT(ADDR(.rodata) - 0xC0000000)
    {
	*(.rodata)
    }

    .data ALIGN(0x1000) : AT(ADDR(.data) - 0xC0000000)
    {
        *(.data)
    }

    .bss ALIGN(0x1000) : AT(ADDR(.bss) - 0xC0000000)
    {
        *(.bss)
    }

    .kstack ALIGN(0x1000) : AT(ADDR(.kstack) - 0xC0000000)
    {
	. += 0x4000;
	*(.kstack)
    }

    .kpages ALIGN(0x1000) : AT(ADDR(.kpages) - 0xC0000000)
    {
	*(.initpages)
    }
}
