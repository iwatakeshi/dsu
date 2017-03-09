%ifndef stdlib_h
%define stdlib_h

section .text
  global atoi

  ; atoi - converts a string to a signed integer
  ; @param edx - a string (buffer) to convert
  ; @return eax - a signed integer
  atoi:
    xor eax, eax
    xor ebx, ebx
    atoi.loop:
      movzx ecx, byte [edx]   ; get a character
      cmp ecx, '-'
      je atoi.negative
      cmp ecx, '0'            ; does character preceed '0'?
      jb  atoi.done           ; then its invalid (we are done)
      cmp ecx, '9'            ; does character follow '9'?
      ja atoi.done
      sub ecx, '0'            ; convert character to number
      imul eax, base          ; multiply eax by base
      add eax, ecx            ; add in current digit
      inc edx                 ; point to next character
      jmp atoi.loop           ; keep converting
    atoi.negative:
      mov ebx, ecx            ; keep the sign
      inc edx                 ; point to next character
      jmp atoi.loop           ; keep converting
    atoi.negate:
      neg eax
      ret
    atoi.done:
      cmp ebx, '-'            ; check if string was negative
      je atoi.negate
      xor edx, edx
      ret

  ; itoa - converts an integer to a string
  ; @param eax - an integer to convert
  ; @param esi - a pointer to the buffer to store the string
  ; @return eax - a pointer to the first character of the generated string
  itoa:
    add esi, 10               ; point to the 10th byte
    mov ebx, base             ; set the base
    mov byte [esi], 10        ; append a line feed
    push eax                  ; store the number for later checks
    test eax, eax             ; check if the number is negative
    jns itoa.loop
    neg eax                   ; negate the number if negative
    itoa.loop:
      xor edx, edx            ; clear edx before dividing edx:eax by ebx
      div ebx                 ; eax /= 10
      add dl, '0'             ; convert the integer to ascii
      dec esi                 ; store the characters in reverse (move the pointer)
      mov [esi], dl           ; copy the converted character to the buffer
      test eax, eax
      jnz itoa.loop           ; repeat until eax == 0
      pop ebx                 ; restore the number
      test ebx, ebx           ; check whether edi is 0
      jns itoa.done
      dec esi
      mov byte [esi], '-'     ; append the minus to the front
    itoa.done:
      mov eax, esi
      ret

section .data
  base equ 10
%endif
