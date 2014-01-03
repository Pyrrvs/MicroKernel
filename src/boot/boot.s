[BITS 32]
[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
mboot:
    dd  MBOOT_HEADER_MAGIC
    dd  MBOOT_HEADER_FLAGS
    dd  MBOOT_CHECKSUM
	
[GLOBAL k_asm_entry]            ; Kernel ASM entry point.
[EXTERN k_start]                ; Kernel C start function.
k_asm_entry:
    cli                         ; Disable interrupts.
    call k_start                ; Call kernel start function
    jmp $                       ; Infinite loop after kernel returns

;;; Constants
MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

