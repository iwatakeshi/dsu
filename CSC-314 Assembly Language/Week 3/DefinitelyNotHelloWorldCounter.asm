section .text
	global _start

_start:							; tells linker entry point

	mov eax, 0				; eax is sum
	jmp for_loop			; just to for loop

	for_loop:
		cmp eax, 10			; compare the number with 10
		je done					; exit the loop if true
		jmp print 			; jump to print the message

	print:
		push eax					; save the number onto the stack
		mov eax, 4				; system call number (sys_write)
		mov ebx, 1				; file descriptor (stdout) / print the value
		mov edx, len			; message length
		mov ecx, msg			; message to write
		int 0x80					; call kernel
		
		pop eax						; pop the stored number from stack and store it into eax
		add eax, 1				; add 1 to eax (eax = eax + 1)
		jmp for_loop			; jump to loop

	done:
		mov eax, 1					; system call number (sys_exit)
		int 0x80						; call kernel

section .data

	msg db "Go away! I refuse to say 'hello, world'",0x0A
	len equ $ - msg
