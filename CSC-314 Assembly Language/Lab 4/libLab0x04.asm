section .data
    header  db `Numbers:\t|\tRunning total:\n`, 0
    output db `\t%d\t|\t%d\n`, 0    
    length db 0
section .bss
    total resd 10
section .text
    global _sumAndPrintList
    extern printf

_sumAndPrintList:

    push ebp
	mov ebp, esp

    sub esp, 4

    push ebx		; program must preserve ebp, ebx, esi, & edi
    push esi
    push edi
    ; ------------------- begin ---------------------- ;
    ; get the *array from stack
    mov esi, [ebp + 8]
    
    ; get the (uint) length from stack
    mov ecx, [ebp + 12]

    ; store the length since printf might mess with ecx
    mov [length], ecx
    
    ; print the header
    push header
    call printf
    add esp, 4

    do:
        ; get the first integer from esi
        mov eax, [esi]
        ; add the running total
        add dword [total], eax

        ; print the numbers and totals
        push dword [total]
        push eax
        push output
        call printf
        add esp, 12

        ; increment the pointer while ecx != 0
        while:
            add esi, 4
            dec dword [length]
            cmp dword [length], 0
            jne do
    mov eax, dword [total]
    ; --------------------- end ---------------------- ;
    pop edi			    ; restore saved registers
	pop esi
	pop ebx

    add esp, 4
	pop ebp
    
    ret