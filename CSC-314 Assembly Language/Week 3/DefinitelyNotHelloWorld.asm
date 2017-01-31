; 'section' nor 'segments'
section .bss
	inputString resb 100	; 'resb' reserve bytes, 100 - how many?
												; the above is a 'directive'
												; inputString is a symbol --> pointer(address) to 1st
												; of the 100 reserved bytes
; 'text' is section for code -- actual instructions
section .text
	global _start

_start:					; a label, defining the entry point for executale
								; 'ld' (linker) needs this
	mov eax, 1000		; storing constant 1000 into register eax
	mov eax, 0xFEDCBA98

	;mov eax, ebx		; copy data from ebx register to eax register
	; mov [eax], ebx	; copy data from ebx register to memory at address
									; stored in eax

; modify so it repeats the messsage 10 times
; use esi or edi register for counter
; inc xxx 			; incremment
; cmp ...				; to do comparison
; jne						; jump if previous comparison was 'not equal'
_setupMessage:				; label ---> an address
	mov edx,len
	mov ecx,msg
	mov ebx,1
	mov eax,4						; 4 is code for the sys_write
	int 0x80						; software interrupt

	jmp _setupMessage		; jump to address _setupMessage

	mov ebx,0
	mov eax,1
	int 0x80						; software interrupt

; 'data' initialized data
section .data

	msg db "Go away! I refuse to say 'hello, world'",0x0A
	len equ $ - msg
