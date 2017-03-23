%ifndef algorithm_h
%define algorithm_h

global reverse

; Reverses the order of the elements in
; a string buffer
; @param eax - A pointer to a string buffer
; @param ecx - The length of the string buffer
reverse:
    xor ebx, ebx
    mov esi, eax                ; point to the start of 'string'
    add eax, ecx                ; move the pointer to the end
    mov edi, eax                ; set edi to point to the end
    dec edi
    shr ecx, 1                  ; set counter to equal (length / 2)
    jz reverse.done             ; check if string is 0 or 1 chars in length
    reverse.loop:
        ; get the chars
        mov al, [esi]
        mov bl, [edi]
        mov [esi], bl           ; swap the chars
        mov [edi], al
        inc esi                 ; move up the esi pointer
        dec edi                 ; move down the edi pointer
        dec ecx                 ; decrement the counter
        jnz reverse.loop        ; keep looping until done
    reverse.done:
        ret

%endif