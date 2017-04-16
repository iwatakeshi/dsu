
section .data
    fmt1 db 'argc = %d', 10, 0
    fmt2 db 'argv[0] =  %s', 10, 0
    fmt3 db 'argv[0][0] = %c', 10, 0
    fmt4 db 'argv[n] = %s', 10, 0

    args_index dd 4
    flag_n     dd 0
    linenum    dd 1
section .bss
    line    resb 10000
    pattern resb 1000
    arg     resb 1000
    args_max    equ 2                  ; maximum # of args to support
    args_count: resd 0              ; # of arguments
    args_len:   resd args_max       ; table of arguments
section .text
    global main
    extern printf
    extern exit
    extern grep
    extern stdin
    extern fgets

main:
    nop                         ; keep gdb happy!
    mov ecx, dword [esp + 4]    ; get argc
    sub ecx, 1                  ; remove that first count (path) from argc
    cmp ecx, 0                  ; if we didn't get anything then we're done
    je exit
    mov dword [args_count], ecx ; store the number of args from argc

    display:
        mov ebx, dword [args_index]     ; get the current index
        mov eax, dword [esp+8]	        ;pointer to argv[0]
         ; copy the argument into edi
        mov esi, dword [eax + ebx]
        mov edi, arg
        mov ecx, 1000
        call strcpy
        call parse
        ; push dword [eax + ebx]		;move to next pointer / argv[1]
        ; push fmt4
        ; call printf
        ; add esp, 8
        add dword[args_index], 4
        dec dword [args_count]
        cmp dword[args_count], 0
        jne display
        
        ; push pattern
        ; push fmt4
        ; call printf
        ; add esp, 8
        ; mov dword[linenum], 0
        while:
            ; call fgets
            push dword [stdin]
            push 1000000
            push line
            call fgets
            cmp eax, 0
            je exit
            
            add esp, 12

            ; call grep
            push dword [linenum]
            push dword [flag_n]
            push pattern
            push line
            call grep

            add esp, 16

            add dword [linenum], 1
            jmp while

	call exit

parse:
    mov esi, arg
    mov al, [esi]
    ; is it a flag?
    cmp al, 45
    jne parse.pattern
    parse.flag:
        inc esi  ; get the next char
        mov al, [esi]
        ; is it 'n'?
        cmp al, 110
        jne exit
        ; set the flag to true
        mov dword [flag_n], 1
        jmp parse.done
    parse.pattern:
        cmp byte [pattern], 0
        jne parse.done
        mov esi, arg
        mov edi, pattern
        mov ecx, 1000
        call strcpy
        parse.done:
            ret

; strcpy - copies a string from a source to destination
; @param esi - the address of the of the source buffer to copy
; @param edi - the address of the destination buffer
; @param ecx - the number of bytes to copy
; @note
; MOVSB copies each byte from ESI to EDI and decrements ECX.
; The exit condition for the REP prefix is when ECX is decremented to zero.
strcpy:
    cld
    rep movsb ; repeat copying bytes from ESI to EDI until ecx = 0
    ret