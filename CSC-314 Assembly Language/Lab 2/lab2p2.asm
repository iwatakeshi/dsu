%include "stdlib.asm"
%include "iostream.asm"
%include "cstdlib.asm"

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
    call wc
    call print_result
    call exit

; wc counts lines, words, and charaters
wc:
    wc.top:
        mov ecx, input
        mov edx, buffer_size
        call read
        mov esi, input
        cmp eax, 0                  ; check if we need to end
        je wc.done
        mov ecx, eax                ; store the length of input
        mov byte [state], OUT       ; set initial state to OUT
        xor eax, eax
    wc.loop:
        mov al, [esi]                   ; c = getchar()
        ; i ++
        inc esi
        ; chars++
        add dword [chars], 1
        ; jc wc.overflow
        ; jo wc.overflow
        
        ; compare
        cmp al, NEWLINE                 ; if (c == '\n') { newline++ }
        je wc.newline
        cmp al, HTAB                    ; if (c == ' ' || c == '\n' || c = '\t' || c == '\r')
        je wc.whitespace_not_newline
        cmp al, VTAB
        je wc.whitespace_not_newline
        cmp al, SPACE
        je wc.whitespace_not_newline
        cmp al, CR
        je wc.whitespace_not_newline
        cmp al, FEED
        je wc.whitespace_not_newline
    
        cmp byte [state], OUT           ;  else if (state == OUT)
        je wc.set_state_to_in
        jmp wc.continue

    wc.newline:
        mov byte [state], OUT           ; state = OUT
        ; newline++
        add dword [lines], 1
        ; jc wc.overflow
    jmp wc.continue

    wc.whitespace_not_newline:          ; alias of set_state_to_out
    wc.set_state_to_out:
         mov byte [state], OUT          ; state = IN;
         jmp wc.continue
    wc.set_state_to_in:
        mov byte [state], IN            ; state = IN;
        ; words++
        add dword [words], 1
        ; jc wc.overflow
    wc.continue:
        dec ecx
        cmp ecx, 0
        je wc.top
        jmp wc.loop
    wc.overflow:
        mov eax, overflow
        call cout
        call exit
    wc.done:
        ret

print_result:
    ; print lines
    mov eax, [lines]
    mov esi, lines_string
    call itoa2
    call cout

    mov eax, space
    call cout

    ; print words
    mov eax, [words]
    mov esi, words_string
    call itoa2

    call cout

    mov eax, space
    call cout

    ; print chars
    mov eax, [chars]
    mov esi, chars_string
    call itoa2
    call cout

    mov eax, newline
    call cout
    ret

section .bss
    input resb 10000000

    state resb 1             ; reserve a byte for boolean values

section .data
    lines dd 0
    words dd 0
    chars dd 0

    lines_string times 10000 dq 0
    words_string times 10000 dq 0
    chars_string times 10000 dq 0

    newline db ' ',0x0a, 0x0
    space   db ' ', 0x0
    debug db 'here',0x0a, 0x00
    overflow db 'An overflow occured', 0x0a, 0x00