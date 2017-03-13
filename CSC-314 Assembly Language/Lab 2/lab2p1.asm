%include "stdlib.asm"
%include "iostream.asm"
%include "cstdlib.asm"
%include "algorithm.asm"
%include "string.asm"
%include "cstring.asm"

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
        mov esi, input
        cmp eax, 0                  ; check if we need to end
        je app.done
        mov dword [string_length], eax
        add dword [chars_read], eax
        mov ecx, eax
        app.main:
            push ecx
            app.scan:
                mov esi, input
                app.scan.loop:
                    mov al, [esi]             ; get the first char from esi
                    inc esi                   ; increment the pointer position
                    add dword [chars], 1      ; increment the characters
                    cmp al, NEWLINE           ; did we find a LF?
                    jne app.scan.loop         ; if not then keep looking
                app.scan.done:
                    ; copy the string
                    mov eax, input
                    mov ecx, [chars]
                    call reverse

                    mov ecx, [chars]
                    mov esi, input
                    sub esi, ecx                ; set the start position for input

                    ; copy the string
                    mov esi, input
                    mov edi, string
                    mov ecx, [chars]
                    ; get the current 'string' position
                    mov dword eax, [chars_read]
                    sub dword eax, [chars]
                    add edi, eax
                    call strcpy
                    mov dword [chars], 0
                    pop ecx
                    dec ecx
                    cmp ecx, 0
                    jne app.top
        app.done:
            mov ecx, string
            mov dword edx, [chars_read]
            call print
            mov ecx, newline
            mov edx, 2
            call print
            ret



section .bss
    input resb 10000000
    string resb 10000000

section .data
    string_length dd 0
    chars dd 0
    chars_read dd 0

    newline db ' ', 0x0a, 0x0
    space   db ' ', 0x0
    debug db 'here',0x0a, 0x00
    overflow db 'An overflow occured', 0x0a, 0x00