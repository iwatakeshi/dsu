section .text
	global sumAtoB
sumAtoB:
	; setup stack frame
	push	ebp
	mov	ebp, esp
	push ebx		; Program must preserve ebp, ebx, esi, & edi
	push esi
	push edi
	;-------------------- start ----------------------
	mov	eax, 0					; store 0 into s (eax)
	mov ebx, dword [ebp + 12] 	; store b into ebx
	mov	ecx, dword [ebp + 8] 	; store a into i (ecx)
	.L1: cmp ecx, ebx
		 jg done
	add eax, dword ecx
	inc ecx
	jmp .L1
	done:
	;-------------------- end ----------------------
	pop edi			; Restore saved registers
	pop esi
	pop ebx
	mov esp,ebp		; Destroy stack frame before returning
	pop ebp
	ret