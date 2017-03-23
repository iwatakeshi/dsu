%ifndef iostream_h
%define iostream_h

%include "string.asm"

section .text

  global cout, cin

  ; cout - prints a string to the console
  ; @param eax - a string to print
  cout:
    push eax
    call slen             ; calculate the length of the output
    mov edx, eax
    pop eax
    mov ecx, eax            ; print the message
    mov eax, 4              ; system call (sys_write)
    mov ebx, 1              ; file descriptor (stdout)
    int 0x80                ; interrupt
    xor eax, eax
    ret

  ; cin - reads a string from the console
  ; @param edi - The destination buffer
  ; @return - The string buffer
  cin:
    mov eax, 3              ; system call (sys_read)
    mov ebx, 0              ; file descriptor (stdin ?)
    mov ecx, input          ; get the input
    mov edx, 10000            ; set the length of input
    int 0x80
    mov ecx, 255
    mov esi, input
    cld
    rep movsb
    ret

section .bss
  input   resb 1000

%endif
