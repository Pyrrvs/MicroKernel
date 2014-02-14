[BITS 32]
[EXTERN vfb_clear]
[EXTERN gdt_load]
[EXTERN idt_init]
[EXTERN kstart]                ; Kernel C start function.
[EXTERN k_pagedir]
[EXTERN kpaging_init]

;;; Constants
STACK_SIZE		equ 0x1000
MBOOT_PAGE_ALIGN	equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO		equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC	equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)
KERNEL_VIRTUAL_BASE	equ 0xC0000000
KERNEL_PAGE_OFFSET	equ (KERNEL_VIRTUAL_BASE >> 20)


[GLOBAL services_start]
[GLOBAL services_end]
[SECTION .services]
services_start:
  resb 0x5000
services_end:

[SECTION .bss]
ALIGN 8
startupStack:
	resb STACK_SIZE	;Allocate 4k of startup stack
topStartupStack:

[SECTION .data]
k_pagetable:	
        %assign i 0
	%rep 1024
		dd (i << 12) | 0x3
		%assign i (i + 1)
        %endrep

[SECTION .text]
ALIGN 4
multiboot_header:
	dd  MBOOT_HEADER_MAGIC
	dd  MBOOT_HEADER_FLAGS
	dd  MBOOT_CHECKSUM

;;; TODO Add stack

[GLOBAL loader]            ; Kernel ASM entry point.
loader equ (_loader - KERNEL_VIRTUAL_BASE)
_loader:
	cli                         ; Disable interrupts.
	mov ecx, (k_pagedir - KERNEL_VIRTUAL_BASE)
	mov edx, (k_pagetable - KERNEL_VIRTUAL_BASE)
	or edx, 0x3
	mov dword [ecx], edx
        mov dword [ecx + KERNEL_PAGE_OFFSET], edx
	mov cr3, ecx
	mov ecx, cr0
	or ecx, 0x80010000
	mov cr0, ecx
	lea ecx, [.higherhalf]
	jmp ecx
.higherhalf:
	mov esp, topStartupStack
	add ebx, KERNEL_VIRTUAL_BASE
	push ebx
	push eax
	call vfb_clear
	call gdt_load		    ; Initialise the GDT
	call idt_init		    ; Initialise the IDT
	call kpaging_init
	call kstart
	pop eax
	pop eax
	jmp $                       ; Infinite loop after kernel returns
