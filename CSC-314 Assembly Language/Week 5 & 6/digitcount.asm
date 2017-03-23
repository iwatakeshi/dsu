%include "iostream.asm"
%include "stdlib.asm"
%include "string.asm"
section .text
  global main

main:

  call prompt

  jmp main

prompt:
  ; prompt for input
  mov eax, prompt0
  call cout
  ; get the input
  mov edi, inputB
  call cin
  ; convert the input to numbers
  mov edx, inputB
  call atoi
  ; convert the digits back to a string
  mov esi, digits
  call itoa
  ; ; calculate the length of the digits string
  ; call strlen
  ; ; ; convert the length to a string
  ; mov esi, digits
  ; call itoa
  ; print the string
  call cout
  ret

; @param eax - the string to count
; @return eax - the length of the string
strlen:
  mov edi, eax ; the string we're scanning
  xor al, al ; That's what we're scanning the string for - a null valued byte
  mov ecx, 0ffffffffh ; we bet on string being null terminated - no hard limit on string scanning
  repne scasb ; Once this finishes, ECX is (0xffffffff - length - 1) (because the terminating null is counted too)
  mov eax, 0fffffffeh
  sub eax, ecx    ; Now eax is (0xffffffff - 1 - ecx), which is string length
  ret


exit:
  mov ebx, 0
  mov eax, 1
  int 0x80

section .bss
  inputB resw 2
  digits resw 2
  result resw 2
section .data
  prompt0 db 'Enter a string of digits to count!', 0x0a, 0x00
