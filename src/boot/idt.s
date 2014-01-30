[GLOBAL idt_load]

idt_load:
	mov eax, [esp+4]  	; Get the IDT pointer
	lidt [eax]        	; Load the IDT pointer.
	ret