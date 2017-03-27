%include "iostream.asm"
%include "cstdlib.asm"
section .data
    message1 db "Enter the character to replace: ", 0x0a, 0
    message1Length equ $-message1

    message2 db "Enter the replacement character: ", 0xa, 0
    message2Length equ $-message2

    message3 db "Enter the text to search and replace: ", 0x0a, 0
    message3Length equ $-message3

    newline db "", 0x0a, 0

section .bss
    character resb 1
    replacement resb 1 
    text resb 10000
    length resd 1

section .text
					
global _start
extern _replaceChar
	
_start:
    
	; begin procedure	

    ; ---- prompt user for character ---- ;

    mov ecx, message1
    mov edx, message1Length
    call print

    mov ecx, character
    mov edx, 2
    call read

    ; ---- prompt user for replacement ---- ;
    mov ecx, message2
    mov edx, message2Length
    call print

    mov ecx, replacement
    mov edx, 2
    call read

    ; ---- prompt user for text ---- ;
    mov ecx, message3
    mov edx, message3Length
    call print

    ; ---- get input and replace the chars ---- ;
    do:
        mov ecx, text
        mov edx, 1000
        call read
        cmp eax, 0
        je done
        mov [length], eax
        ; pass the params
        push dword [replacement]
        push dword [character]
        push dword [length]
        push text
        ; replace the chars
        call _replaceChar

        ; restore stack pointer
        add esp, 4

        mov ecx, eax
        mov edx, [length]
        call print
        while: jmp do

        done:
            call exit