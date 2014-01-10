[BITS 32]
[section .text]
[GLOBAL gdt_load]
gdt_load:
	mov eax, [esp+4]  	; Retrieve GDT pointer
	lgdt [eax]        	; Load the new GDT pointer
	
	;; Set DS, ES, FS, GS and SS to 0x10 (i.e. 3rd entry in GDT)
	mov ax, 0x10      	; 0x10 == Ring 0's DS
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	;; Set CS to 0x08 (i.e. 2nd entry in GDT)
	jmp 0x08:.load   	; far jump is the only way to set CS
.load:
	ret
