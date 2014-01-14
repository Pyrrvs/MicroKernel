ENTRY(k_asm_entry)
OUTPUT_FORMAT(elf32-i386)
SECTIONS
{
    . = 0x100000;
    .text ALIGN(4096) :
    {
        *(.text)
    }

    .rodata ALIGN(4096) :
    {
	*(.rodata)
    }

    .data ALIGN(4096) :
    {
        *(.data)
    }

    .bss ALIGN(4096) :
    {
        *(.bss)
    }

    .kstack ALIGN(4096) :
    {
	. += 0x4000;
	*(.kstack)
    }

    .kpages ALIGN(4096) :
    {
	*(.initpages)
    }
}
