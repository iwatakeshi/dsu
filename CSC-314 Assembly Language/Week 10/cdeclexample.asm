section .data
section .bss

    x resb 4
    y resb 4
    maximum resb 4

section .text

    global _start
    extern max

_start:

    ; main program does whatever
    ; until 'something' is called

    ; call something

    ; optional but save eax, ecx, edx
    push eax
    push ecx
    push edx

    ; push params on the stack

    push [x]
    push [y]

    call something

    add esp, 8

    ; do whatever with eax
    mov [maximum], eax
    ; restore eax, ecx, edx
