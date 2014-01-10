[BITS 32]
[EXTERN putnbr]
[EXTERN putc]
[EXTERN vfb_clear]
[EXTERN gdt_init]
[EXTERN k_start]                ; Kernel C start function.

;;; Constants
STACK_SIZE		equ 0x4000
MBOOT_PAGE_ALIGN	equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO		equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC	equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[SECTION .bss]
startupStack:
	align 4
	resb STACK_SIZE	;Allocate 16k of startup stack
topStartupStack:
	
[SECTION .text]
ALIGN 4
multiboot_header:
	dd  MBOOT_HEADER_MAGIC
	dd  MBOOT_HEADER_FLAGS
	dd  MBOOT_CHECKSUM

;;; TODO Add stack

[GLOBAL k_asm_entry]            ; Kernel ASM entry point.
k_asm_entry:
	cli                         ; Disable interrupts.	
	push ebx
	push eax
	call gdt_init		    ; Initialise the GDT
	call k_start                ; Call kernel start function
	jmp $                       ; Infinite loop after kernel returns
