section .bss
    character resb 0
    replacement resb 0 
    text resd 0
    length resd 0
section .text

    global _replaceChar

_replaceChar:
    sub esp, 20

    ; get the *text from stack
    mov edx, [ebp + 16]
    mov [text], edx
    
    ; get the (uint) length from stack
    mov edx, [ebp + 12]
    mov [length], edx
    
    ; get the (char) character from stack
    mov edx, [ebp + 8]
    mov [character], edx

    ; get the (char) replacement from stack
    mov edx, [ebp + 4]
    mov [replacement], edx