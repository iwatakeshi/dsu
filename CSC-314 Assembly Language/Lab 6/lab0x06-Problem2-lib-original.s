	.file	"lab0x06-Problem2-lib-original.c"
	.intel_syntax noprefix
	.text
	.globl	sumAtoB
	.type	sumAtoB, @function
sumAtoB:
.LFB0:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 16
	call	__x86.get_pc_thunk.ax
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	mov	eax, DWORD PTR 8[ebp]
	mov	DWORD PTR -8[ebp], eax
	mov	DWORD PTR -4[ebp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR -8[ebp]
	add	DWORD PTR -4[ebp], eax
	add	DWORD PTR -8[ebp], 1
.L2:
	mov	eax, DWORD PTR -8[ebp]
	cmp	eax, DWORD PTR 12[ebp]
	jle	.L3
	mov	eax, DWORD PTR -4[ebp]
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	sumAtoB, .-sumAtoB
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB1:
	.cfi_startproc
	mov	eax, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE1:
	.ident	"GCC: (Ubuntu 6.2.0-5ubuntu12) 6.2.0 20161005"
	.section	.note.GNU-stack,"",@progbits
