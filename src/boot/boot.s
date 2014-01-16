[BITS 32]
[EXTERN putc]
[EXTERN vfb_clear]
[EXTERN gdt_load]
[EXTERN idt_init]
[EXTERN kpaging_init]
[EXTERN k_start]                ; Kernel C start function.

;;; Constants
STACK_SIZE		equ 0x1000
MBOOT_PAGE_ALIGN	equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO		equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC	equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)
KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  ; Page directory index of kernels 4MB PTE.

[SECTION .data]
ALIGN 0x1000
BootPageDirectory:
    dd 0x00000083
    times (KERNEL_PAGE_NUMBER - 1) dd 0
    dd 0x00000083
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0

[SECTION .kstack]
startupStack:
	align 4096
	resb STACK_SIZE	;Allocate 4k of startup stack
topStartupStack:
	
[SECTION .text]
ALIGN 4
multiboot_header:
	dd  MBOOT_HEADER_MAGIC
	dd  MBOOT_HEADER_FLAGS
	dd  MBOOT_CHECKSUM

;;; TODO Add stack

[GLOBAL k_asm_entry]
k_asm_entry equ (_k_asm_entry - 0xC0000000)

[GLOBAL _k_asm_entry]            ; Kernel ASM entry point.
_k_asm_entry:
	kpaging_init
	mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
	mov cr3, ecx

	mov ecx, cr4
	or ecx, 0x00000010
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000000
	mov cr0, ecx
	lea ecx, [StartInHigherHalf]
	jmp ecx

StartInHigherHalf:
	mov dword [BootPageDirectory], 0
	invlpg [0]

	cli                         ; Disable interrupts.                                                                                               
	call vfb_clear
	push '*'
	call putc
	pop eax
	jmp $                       ; Infinite loop after kernel returns
