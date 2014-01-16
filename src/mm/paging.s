[SECTION .text]
[GLOBAL switch_page_directory]
[EXTERN putnbr]
[EXTERN putc]
	
switch_page_directory:
	mov eax, [esp+4]	; Get the page_directory pointer
	mov cr3, eax
	mov ebx, cr0
	or ebx, 0x80010000
	mov cr0, ebx
	ret