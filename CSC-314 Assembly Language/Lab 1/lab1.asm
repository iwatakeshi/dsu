%include "iostream.asm"
%include "string.asm"
%include "stdlib.asm"
%include "fibonacci.asm"

section .text
  global _start
_start:
  call main

main:
  call prompt
  mov edx, seed1
  call atoi                   ; convert seed1 to int (stored in eax)
  push eax                    ; store seed1 into the stack
  mov edx, seed2
  call atoi                   ; convert seed2 to int
  push eax                    ; store seed2 into the stack
  mov edx, step
  call atoi                   ; convert step1 to int
  push eax                    ; store step into stack

  ; prepare for fibonacci
  pop ecx                     ; get the count
  pop ebx                     ; get the second input
  pop eax                     ; get the first input

  call fibonacci              ; start it up!
  call exit                   ; yup we're done!

prompt:
  ; prompt for seed1
  mov eax, prompt1
  call cout
  mov edi, seed1
  call cin
  ; prompt for seed2
  mov eax, prompt2
  call cout
  mov edi, seed2
  call cin
  ; prompt for steps
  mov eax, prompt3
  call cout
  mov edi, step
  call cin
  ret

exit:
  mov ebx, 0
  mov eax, 1
  int 0x80


section .bss
  seed1   resb 20
  seed2   resb 20
  step    resb 20

section .data

  prompt1 db 'Enter a digit for seed 1', 0x0a, 0x00
  prompt2 db 'Enter a digit for seed 2', 0x0a, 0x00
  prompt3 db 'Enter the number of steps', 0x0a, 0x00
