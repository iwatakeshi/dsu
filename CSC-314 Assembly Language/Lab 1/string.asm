%ifndef string_h
%define string_h
section .text
  global slen

  ; http://int80h.org/strlen/
  ; slen - calculates the length of a string
  ; @param eax - the string the calculate
  ; @return eax - the length of the string
  slen:
    mov edi, eax
  	push	edi
  	sub	ecx, ecx
  	mov	edi, [esp+8]
  	not	ecx
  	sub	al, al
  	cld
    repne	scasb
  	not	ecx
  	pop	edi
  	lea	eax, [ecx-1]
  	ret

%endif
