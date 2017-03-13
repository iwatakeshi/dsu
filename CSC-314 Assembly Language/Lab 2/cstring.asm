%ifndef cstring_h
%define cstring_h
  global strcpy, strcpy2, strcpy3
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

    ; strcpy - copies a string from a source to destination
    ; @param esi - the address of the of the source buffer to copy
    ; @param edi - the address of the destination buffer
    ; @note
    ; strcpy2 will copy until an ascii zero is found, assuming that the string
    ; is null (zero) terminated
    strcpy2:
      cld
      strcpy2.loop:
        lodsb                     ; load byte from source into AL and inc ESI
        stosb                     ; write AL to dest and inc EDI
        cmp al, 0                 ; see if its an ascii zero
        jne strcpy2.loop          ; read the next byte if its not
      ret

    ; strcpy - copies a string from a source to destination
    ; @param esi - the address of the of the source buffer to copy
    ; @param edi - the address of the destination buffer
    ; @note
    ; strcpy3 is similar to strcpy2 but the cld does not effect this method
    ; and you can use any 32 bit registers when you are not using the string
    ; instructions.
    strcpy3:
      strcpy3.loop:
        mov al, [esi]             ; copy byte at address in esi to al
        inc esi                   ; increment address in esi
        mov [edi], al             ; copy byte in al to address in edi
        inc edi                   ; increment address in edi
        cmp al, 0                 ; see if its an ascii zero
        jne strcpy3.loop          ; jump back and read next byte if not
      ret

%endif
