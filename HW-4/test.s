	.file	"test.c"
	.text
	.globl	bubble_a
	.type	bubble_a, @function
bubble_a:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$32, %esp
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	.L2
.L6:
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	$0, -20(%ebp)
	jmp	.L3
.L5:
	movl	-12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jge	.L4
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%edx, (%eax)
	movl	-12(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
.L4:
	addl	$1, -20(%ebp)
	addl	$4, -12(%ebp)
.L3:
	movl	-20(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jl	.L5
	subl	$1, -16(%ebp)
.L2:
	cmpl	$0, -16(%ebp)
	jg	.L6
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	bubble_a, .-bubble_a
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
