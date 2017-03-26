section .bss
    character resb 0
    replacement resb 0 
    text resd 0
    length resd 0
section .text

    global _replaceChar

_replaceChar:
    push ebp		; set up stack frame for debugger
	mov ebp, esp
	push ebx		; program must preserve ebp, ebx, esi, & edi
	push esi
	push edi

    sub esp, 20

    ; get the *text from stack
    mov edx, [ebp + 16]
    mov [text], edx
    
    ; get the (uint) length from stack
    mov edx, [ebp + 12]
    mov [length], edx
    
    ; get the (char) character from stack
    mov edx, [ebp + 8]
    mov [character], edx

    ; get the (char) replacement from stack
    mov edx, [ebp + 4]
    mov [replacement], edx

    pop edi			    ; restore saved registers
	pop esi
	pop ebx
	mov esp, ebp		; destroy stack frame before returning
	pop ebp
    
    ret