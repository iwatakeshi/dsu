%include "iostream.asm"
%include "cstdlib.asm"
section .data
    message1 db "Enter the character to replace: "
    message1Length equ $-message1

    message2 db "Enter the replacement character: "
    message2Length equ $-message2

    message3 db "Enter the text to search and replace: ", 0xa, 0
    message3Length equ $-message3
section .bss
    character resb 0
    replacement resb 0 
    text resd 0
    length resd 0

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
    mov edx, 1
    call read

    ; ---- prompt user for replacement ---- ;
    mov ecx, message2
    mov edx, message2Length
    call print

    mov ecx, replacement
    mov edx, 1
    call read

    ; ---- prompt user for text ---- ;
    mov ecx, message3
    mov edx, message3Length
    call print

    do:
        mov ecx, text
        mov edx, 1000
        call read
        mov [length], eax
        ; pass params
        push replacement
        push character
        push dword [length]
        push text
        ; replace(text, length, character, replacement)
        call _replaceChar
        add esp, 20
        while: cmp eax, 0
               jne do
	; ret			        ; return control to Linux
    call exit