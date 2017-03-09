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
    call print_result
    call exit


app:
    app.top:
        mov ecx, input
        mov edx, buffer_size
        call read
        ;---------------------------------
        cmp eax, buffer_size
        jl app.input_ok
        cmp byte [ecx + edx - 1], 10
        je app.input_ok
        mov byte[ecx + edx - 1], 10
        call cout.clear
        ;---------------------------------
        app.input_ok:
            mov esi, input
            cmp eax, 0                  ; check if we need to end
            je app.done
            mov ecx, eax                ; store the length of input
            mov byte [state], OUT       ; set initial state to false
            xor eax, eax
        
            mov ebx, temp
    app.loop:
        mov al, [esi]                   ; c = getchar()
        
        ; chars++
        add byte [chars], 1
        ; collect the characters
        mov [ebx], al
        inc ebx
        ; compare
        cmp al, NEWLINE                 ; if (c == '\n')
        je app.whitespace
        cmp al, HTAB                    ; if (c == ' ' || c == '\n' || c = '\t' || c == '\r')
        je app.whitespace
        cmp al, VTAB
        je app.whitespace
        cmp al, SPACE
        je app.whitespace
        cmp al, CR
        je app.whitespace
        cmp al, FEED
        je app.whitespace

        cmp byte [state], OUT           ;  else if (state == OUT)
        je app.set_state_to_in
        jmp app.continue

    app.whitespace:          ; alias of set_state_to_out
    app.set_state_to_out:
        mov byte [state], OUT          ; state = OUT;
        ; save the states
        push ecx
        push esi
        push ebx
        sub ebx, [chars]
        push ebx

        ; reverse the string
        mov eax, ebx                    ; set the string to reverse
        mov ecx, [chars]                     ; pop and save the string length
        call reverse                    ; reverse it
        
        mov ecx, [chars]
        xor eax, eax
        pop esi
        mov edi, string
        add edi, [string_length]
        ; add esi, [string_length];
        ; sub esi, [chars]
        ; append it to the string
        app.append:
            mov al, [esi]
            mov byte [edi], al
            inc esi
            inc edi
            loop app.append
        
        mov ecx, [chars]
        add [string_length], ecx
        mov byte [chars], 0
        ; restore the states
        pop ebx
        pop esi
        pop ecx
        jmp app.continue
    app.set_state_to_in:
        mov byte [state], IN            ; state = IN;
    app.continue:
        ; i ++
        inc esi
        dec ecx
        cmp ecx, 0
        je app.top
        jmp app.loop
    app.overflow:
        mov eax, overflow
        call cout
        call exit
    app.done:
        ret

print_result:
    mov eax, string                 ; set the string
    call slen                       ; get the length again
    mov ecx, string                 ; set the string
    mov edx, eax                    ; set the length
    call print                      ; print it

    mov eax, newline
    call cout
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