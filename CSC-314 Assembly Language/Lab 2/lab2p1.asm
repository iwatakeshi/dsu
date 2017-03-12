%include "stdlib.asm"
%include "iostream.asm"
%include "cstdlib.asm"
%include "algorithm.asm"
%include "string.asm"

%define NEWLINE 10
%define CR 13
%define HTAB 9
%define SPACE 32
%define VTAB 11
%define FEED 12

%define OUT 0
%define IN 1


section .text

    global _start

_start:
    call app
    call exit

app:
    app.top:
        mov ecx, input
        mov edx, buffer_size
        call read
        ;---------------------------------
        cmp eax, buffer_size
        jl app.main
        cmp byte [ecx + edx - 1], 10
        je app.main
        mov byte[ecx + edx - 1], 10
        call cout.clear
        ;---------------------------------
        app.main:
            mov esi, input
            cmp eax, 0                  ; check if we need to end
            je app.done
            mov ecx, eax                ; store the length of input
            
            push eax
            
            mov eax, input
            ; ecx already has the length
            call reverse

            mov ecx, input
            pop edx
            call print
        app.done:
            ; mov eax, string
            ; call slen
            ; mov ecx, string
            ; mov edx, eax
            ; call print
            ; mov eax, newline
            ; call cout
            ret



section .bss
    input resb 10000000
    string resb 10000000
    temp resb 10000000
    state resb 1             ; reserve a byte for boolean values
    
    chars resb 100

section .data
    string_length dw 0
                 dw 0
    newline db ' ',0x0a
    space   db ' ',0x0
    debug db 'here',0x0a, 0x00
    overflow db 'An overflow occured', 0x0a, 0x00