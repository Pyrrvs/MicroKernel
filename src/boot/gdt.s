[BITS 32]
[SECTION .data]
gdt_ptr:
	dw gdt_end - gdt - 1
	dd gdt

gdt:
	dd 0, 0
	db 0xFF, 0xFF, 0, 0, 0, 0x9A, 0xCF, 0
	db 0xFF, 0xFF, 0, 0, 0, 0x92, 0xCF, 0
	db 0xFF, 0xFF, 0, 0, 0, 0xFA, 0xCB, 0
	db 0xFF, 0xFF, 0, 0, 0, 0xF2, 0xCB, 0
gdt_end:
	
[SECTION .text]
[GLOBAL gdt_load]
[EXTERN puts]
gdt_load:
	lgdt [gdt_ptr]        	; Load the new GDT pointer
	
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
