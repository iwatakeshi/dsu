section .data
    offset db 0

section .text
    global reverse

reverse:
    ; prepare for calling conventions
    push ebp
	mov ebp,esp
    ;  program must preserve ebp, ebx, esi, & edi
	push ebx
    push edx
	push esi
	push edi
	; ------------------- begin ---------------------- ;	
    ; get the *input from stack
    mov edx, [ebp + 8]

    ;get the (uint) length from stack
    mov ecx, [ebp + 12]

    ; save the length for later
    push ecx

    ; point to the input
    mov esi, edx
    mov edi, edx    
    ; begin reversal
    L1:
        L2:
            ; skip newline
            mov al, [edi]
            cmp al, 10
            jne L2.done
            inc edi
            dec ecx
            cmp ecx, 0
            je L1.done
            jmp L2
            L2.done:
        ; get the line
        L3:
            mov al, [edi]
            cmp al, 10
            je L3.done
            inc edi
            inc ebx
            dec ecx
            jmp L3
            L3.done:
        ; edx holds the new position
        mov edx, edi
        inc edx
        ; newline found
        ; position the pointer to the char before newline
        sub edi, 1
        sub ebx, 1
        ; lets reverse the input
        
        ; length / 2
        shr ebx, 1
        L4:
            cmp ebx, 0
            je L4.done
            mov al, [esi]
            mov ah, [edi]
            mov [esi], ah
            mov [edi], al
            inc esi
            dec edi
            dec ebx
            jmp L4
            L4.done:
        ; esi now points the beginning of a new line
        mov esi, edx
        mov edi, edx
        dec ecx
        jnz L1
        L1.done:

        
        
    ; restore the length
    pop eax
        
	; --------------------- end ---------------------- ;
	; restore saved registers
    pop edi
	pop esi
    pop edx
	pop ebx
    ; destroy stack frame before returning
	mov esp,ebp
	pop ebp
	; return
    ret