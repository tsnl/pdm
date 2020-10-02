	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 16
	.globl	_fibonacci              ## -- Begin function fibonacci
	.p2align	4, 0x90
_fibonacci:                             ## @fibonacci
	.cfi_startproc
## %bb.0:                               ## %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	testq	%rdi, %rdi
	je	LBB0_1
## %bb.2:                               ## %ite-false
	movq	%rdi, %rbx
	movl	$1, %eax
	cmpq	$1, %rdi
	je	LBB0_4
## %bb.3:                               ## %ite-false3
	leaq	-1(%rbx), %rdi
	callq	_fibonacci
	movq	%rax, %r14
	addq	$-2, %rbx
	movq	%rbx, %rdi
	callq	_fibonacci
	addq	%r14, %rax
	jmp	LBB0_4
LBB0_1:
	xorl	%eax, %eax
LBB0_4:                                 ## %ite-landing
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
