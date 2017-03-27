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
    xor ebx, ebx
    do:
        ; get the first char from esi
        mov dl, [esi]
        ; check if we found the character
        cmp dl, al
        ; if not then continue the loop
        jne while
        ; otherwise replace the char
        mov byte [esi], ah
        ; and keep track of the number of replacements
        inc ebx
        ; move the char position forward while ecx != 0
        ; then decrecment the counter and loop
        while: inc esi
            loop do
    
    pop ecx
    ; point to the beginning of cstring
    sub esi, ecx
    mov [ebp + 8], esi
    ; return the number of replacements
    mov eax, ebx

    ; --------------------- end ---------------------- ;
    pop edi			    ; restore saved registers
	pop esi
	pop ebx

    add esp, 4
	pop ebp
    
    ret