%ifndef string_h
%define string_h
section .text
  global slen

; slen:
;     mov edi, eax
;     push  ebx                 ; save any registers that 
;     push  ecx                 ; we will trash in here

;     mov   ebx, edi            ; ebx = edi

;     xor   al, al              ; the byte that the scan will
;                             ; compare to is zero

;     mov   ecx, 0xffffffff     ; the maximum number of bytes
;                             ; i'm assuming any string will
;                             ; have is 4gb

;     repne scasb               ; while [edi] != al, keep scanning

;     sub   edi, ebx            ; length = dist2 - dist1
;     mov   eax, edi            ; eax now holds our length

;     pop   ecx                 ; restore the saved registers
;     pop   ebx

;     ret                       ; all done!



slen:
    push ebx
    push ecx
    push edx

    mov esi, eax
    xor ecx, ecx
    slen.loop:
        cmp byte [esi], 0
        jz slen.done
        inc esi
        inc ecx
        jmp slen.loop
    slen.done:
        mov eax, ecx
        pop edx
        pop ecx
        pop ebx
        ret 

%endif
