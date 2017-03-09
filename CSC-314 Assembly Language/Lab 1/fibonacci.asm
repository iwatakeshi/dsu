%ifndef fibonacci_h
%define fibonacci_h

%include "stdlib.asm"
%include "iostream.asm"

section .text
  global fibonacci

; fibonacci - generates and prints a sequence of primes
; @param eax - the first seed
; @param ebx - the second seed
; @param ecx - the number of sequences to print
fibonacci:
  ; print the first value
  mov edx, eax
  call fibonacci.print
  ; print the second value
  mov edx, ebx
  call fibonacci.print
  ; prepare for sequence
  xor edx, edx                ; clear edx
  test ecx, ecx               ; check if the third is negative
  js fibonacci.negate

  fibonacci.checkpoint:
    dec ecx                   ; n - 1
    fibonacci.loop:
      add eax, ebx            ; store the next value into eax (next = first + second)
      mov edx, eax            ; copy the next value into memory
      mov eax, ebx            ; copy the second value to the first
      mov ebx, edx            ; copy the next value into the second
      call fibonacci.print
      test ecx, ecx           ; check if we should proceed
      je fibonacci.done
      loop fibonacci.loop
      jmp fibonacci.done
    fibonacci.negate:
      neg ecx
      jmp fibonacci.checkpoint
    fibonacci.done:
      mov eax, edx
      ret
    fibonacci.print:
      pusha
      mov eax, edx
      mov esi, buffer
      call itoa
      call cout
      mov byte [buffer], 0
      popa
      ret
    ret

section .bss

  buffer  resw 3

%endif
