global _replaceChar

section .text

_replaceChar:

    push ebp
	mov ebp, esp
    

    sub esp, 4

    push ebx		; program must preserve ebp, ebx, esi, & edi
    push esi
    push edi
    ; ------------------- begin ---------------------- ;
    ; get the *text from stack
    mov esi, [ebp + 8]
    
    ; get the (uint) length from stack
    mov ecx, [ebp + 12]
    
    ; get the (char) character from stack
    mov al, byte [ebp + 16]

    ; get the (char) replacement from stack
    mov ah, byte [ebp + 20]

    push ecx
    do:
        ; get the first char from esi
        mov dl, [esi]
        ; check if we found the character
        cmp dl, al
        ; if not then continue the loop
        jne while
        ; otherwise replace the char
        mov byte [esi], ah
        ; decrecment the counter and loop
        ; move the char position forward while ecx != 0
        while: inc esi
            loop do
    
    pop ecx
    ; point to the beginning of cstring
    sub esi, ecx
    ; return the pointer!
    mov eax, esi

    ; --------------------- end ---------------------- ;
    pop edi			    ; restore saved registers
	pop esi
	pop ebx

    add esp, 4
	; mov esp, ebp		; destroy stack frame before returning
	pop ebp
    
    ret