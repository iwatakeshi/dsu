%include "iostream.asm"
%include "cstdlib.asm"

section .bss
    input resb 10000

section .data
    
section .text

    global _start
    extern reverse

_start:

    ; read the input
        mov ecx, input
        mov edx, 10000
        call read
        cmp eax, 0
        je done
    ; reverse the input
        push eax        ; store the length into the stack
        push input      ; store the address of input into the stack
        call reverse    ; reverse the input and return the length (eax)
        sub esp, 2      ; restore the stack position
    ; print the text
        mov ecx, input
        mov edx, eax
        call print
        jmp _start
    done:
    ; exit
        call exit