[BITS 32]

esp0_ofs equ 4
ss0_ofs equ 8

[SECTION .bss]
[GLOBAL tss0]
tss0:
	resb 104
	
[SECTION .data]
gdt_ptr:
	dw gdt_end - gdt - 1
	dd gdt

[GLOBAL gdt]
gdt:
	dd 0, 0
	db 0xFF, 0xFF, 0, 0, 0, 0x9A, 0xCF, 0
	db 0xFF, 0xFF, 0, 0, 0, 0x92, 0xCF, 0
	db 0xFF, 0xFF, 0, 0, 0, 0xFA, 0xCF, 0
	db 0xFF, 0xFF, 0, 0, 0, 0xF2, 0xCF, 0
tss_sel:db 0x68, 0, 0, 0, 0, 0x89, 0, 0
gdt_end:

[SECTION .text]
[GLOBAL gdt_load]
[EXTERN puts]
gdt_load:
	;; Set TSS Selector and TSS0
	mov word[tss0 + ss0_ofs], 0x10
	mov eax, tss0	
	mov byte [tss_sel + 2], al
	mov byte [tss_sel + 3], ah
	shr eax, 16
	mov byte [tss_sel + 4], al
	mov byte [tss_sel + 7], ah

	lgdt [gdt_ptr]        	; Load the new GDT pointer

	;; Load TSS Selector
	mov ax, 0x28
	ltr ax
	
	;; Set DS, ES, FS, GS and SS to 0x10 (i.e. 3rd entry in GDT)
	mov ax, 0x10      	; 0x10 == Ring 0's DS
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	;; Set CS to 0x08 (i.e. 2nd entry in GDT)
	jmp 0x08:.loaded   	; far jump is the only way to set CS
.loaded:
	push loaded_msg
	call puts
	pop eax
	ret

[SECTION .rodata]
loaded_msg:	
	db "GDT loaded", 10, 0
