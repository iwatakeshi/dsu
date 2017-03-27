section .bss
section .text

    global max

max:

    ; take 2 integers and return the larger values
    
    push ebp
    mov ebp, esp

    ; reserve space for local variables in c-style
    sub esp, 4
    
    push ebx
    push esi
    push edi

    mov edx, [ebp + 8]
    mov ecx, [ebp + 12]

    ; if a > b
    cmp ecx, edx
    jg maxIsECX
    mov eax, edx
    jmp done

    maxIsECX:
        mov eax, ecx

    done: 
        pop edi
        pop esi
        pop edi
        add esp, 4
        pop ebp
        ret
