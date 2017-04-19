	.file	"lab0x06-Problem2-main.c"
	.intel_syntax noprefix
	.section	.rodata
	.align 4
.LC2:
	.string	"Number of Calls to sumAtoB: %d, m=%d, n=%d, Result=%d,  Total time spent in sumAtoB: %Lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	lea	ecx, 4[esp]
	.cfi_def_cfa 1, 0
	and	esp, -16
	push	DWORD PTR -4[ecx]
	push	ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	mov	ebp, esp
	push	ebx
	push	ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	sub	esp, 64
	call	__x86.get_pc_thunk.bx
	add	ebx, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_
	fldz
	fstp	TBYTE PTR -32[ebp]
	mov	DWORD PTR -52[ebp], 0
	jmp	.L2
.L4:
	mov	eax, DWORD PTR -52[ebp]
	sub	eax, 32000
	mov	DWORD PTR -48[ebp], eax
	call	clock@PLT
	mov	DWORD PTR -44[ebp], eax
	sub	esp, 8
	push	DWORD PTR -52[ebp]
	push	DWORD PTR -48[ebp]
	call	sumAtoB@PLT
	add	esp, 16
	mov	DWORD PTR -40[ebp], eax
	call	clock@PLT
	mov	DWORD PTR -36[ebp], eax
	mov	eax, DWORD PTR -36[ebp]
	sub	eax, DWORD PTR -44[ebp]
	mov	DWORD PTR -60[ebp], eax
	fild	DWORD PTR -60[ebp]
	fld	TBYTE PTR .LC1@GOTOFF[ebx]
	fdivp	st(1), st
	fstp	TBYTE PTR -20[ebp]
	fld	TBYTE PTR -32[ebp]
	fld	TBYTE PTR -20[ebp]
	faddp	st(1), st
	fstp	TBYTE PTR -32[ebp]
	mov	ecx, DWORD PTR -52[ebp]
	mov	edx, 274877907
	mov	eax, ecx
	imul	edx
	sar	edx, 7
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	imul	eax, eax, 2000
	sub	ecx, eax
	mov	eax, ecx
	test	eax, eax
	jne	.L3
	push	DWORD PTR -24[ebp]
	push	DWORD PTR -28[ebp]
	push	DWORD PTR -32[ebp]
	push	DWORD PTR -40[ebp]
	push	DWORD PTR -52[ebp]
	push	DWORD PTR -48[ebp]
	push	DWORD PTR -52[ebp]
	lea	eax, .LC2@GOTOFF[ebx]
	push	eax
	call	printf@PLT
	add	esp, 32
.L3:
	add	DWORD PTR -52[ebp], 1
.L2:
	cmp	DWORD PTR -52[ebp], 64000
	jle	.L4
	nop
	lea	esp, -8[ebp]
	pop	ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	lea	esp, -4[ecx]
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
	.align 16
.LC1:
	.long	0
	.long	4096000000
	.long	16402
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB3:
	.cfi_startproc
	mov	ebx, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE3:
	.ident	"GCC: (Ubuntu 6.2.0-5ubuntu12) 6.2.0 20161005"
	.section	.note.GNU-stack,"",@progbits
