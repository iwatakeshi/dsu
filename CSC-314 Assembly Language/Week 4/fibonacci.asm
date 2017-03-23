section .bss
  buff resb 4        ; reserve 4 bytes (32 bits) into the buffer

section .text
    global _start:
    seed0 equ 0
    seed1 equ 1

_start:
    mov eax, seed0    ; set initial value to 0 (first)
    mov ebx, seed1    ; set initial value to 1 (second)
    call fibonacci
    jmp done          ; end the sequence
  fibonacci:
    add eax, ebx      ; store the next value into eax (next = first + second)
    mov [buff], eax   ; copy the next value into the buffer
    mov eax, ebx      ; copy the second value to the first
    mov ebx, [buff]   ; copy the next value into the second
    call print
    jno fibonacci

  print:
    push eax          ; temporarily store the first
    push ebx          ; temporarily store the second
    mov eax, 4        ; system call number (sys_write)
    mov ebx, 1        ; file descriptor (stdout)
    mov edx, 4        ; length of message
    mov ecx, buff     ; print the message
    int 0x80          ; call kernel (system interrupt)
    pop ebx           ; restore second
    pop eax           ; restore first
    ret               ; return

    done:
      mov eax, 1					; system call number (sys_exit)
      int 0x80						; call kernel

section .data
