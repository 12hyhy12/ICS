	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_cread_alt
	.align	4, 0x90
_cread_alt:                             ## @cread_alt
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movq	$0, -8(%rbp)
	testq	%rdi, %rdi
	leaq	-8(%rbp), %rax
	cmovneq	%rdi, %rax
	movq	(%rax), %rax
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
