	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_bubble_a
	.align	4, 0x90
_bubble_a:                              ## @bubble_a
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	pushl	%eax
	movl	12(%ebp), %ecx
	cmpl	$2, %ecx
	jl	LBB0_11
## BB#1:                                ## %.lr.ph.preheader.preheader
	movl	8(%ebp), %eax
	testb	$1, %cl
	movl	%ecx, %ebx
	jne	LBB0_5
## BB#2:                                ## %.lr.ph.preheader.prol
	leal	-1(%ecx), %ecx
	movl	(%eax), %edx
	xorl	%esi, %esi
	.align	4, 0x90
LBB0_3:                                 ## %.lr.ph.prol
                                        ## =>This Inner Loop Header: Depth=1
	movl	4(%eax,%esi,4), %ebx
	cmpl	%edx, %ebx
	movl	%edx, %edi
	cmovlel	%ebx, %edi
	xorl	%edx, %ebx
	movl	%edi, (%eax,%esi,4)
	xorl	%edi, %ebx
	movl	%ebx, 4(%eax,%esi,4)
	incl	%esi
	cmpl	%ecx, %esi
	movl	%ebx, %edx
	jl	LBB0_3
## BB#4:
	movl	%ecx, %ebx
	movl	12(%ebp), %ecx
LBB0_5:                                 ## %.lr.ph.preheader.preheader.split
	cmpl	$2, %ecx
	je	LBB0_11
	.align	4, 0x90
LBB0_6:                                 ## %.lr.ph.preheader
                                        ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_7 Depth 2
                                        ##     Child Loop BB0_9 Depth 2
	movl	%ebx, -16(%ebp)         ## 4-byte Spill
	leal	-1(%ebx), %edx
	movl	(%eax), %ecx
	xorl	%esi, %esi
	.align	4, 0x90
LBB0_7:                                 ## %.lr.ph
                                        ##   Parent Loop BB0_6 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	4(%eax,%esi,4), %ebx
	cmpl	%ecx, %ebx
	movl	%ecx, %edi
	cmovlel	%ebx, %edi
	xorl	%ecx, %ebx
	movl	%edi, (%eax,%esi,4)
	xorl	%edi, %ebx
	movl	%ebx, 4(%eax,%esi,4)
	incl	%esi
	cmpl	%edx, %esi
	movl	%ebx, %ecx
	jl	LBB0_7
## BB#8:                                ## %.loopexit
                                        ##   in Loop: Header=BB0_6 Depth=1
	movl	-16(%ebp), %ebx         ## 4-byte Reload
	addl	$-2, %ebx
	movl	(%eax), %esi
	xorl	%edx, %edx
	.align	4, 0x90
LBB0_9:                                 ## %.lr.ph.1
                                        ##   Parent Loop BB0_6 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	4(%eax,%edx,4), %ecx
	cmpl	%esi, %ecx
	movl	%esi, %edi
	cmovlel	%ecx, %edi
	xorl	%esi, %ecx
	movl	%edi, (%eax,%edx,4)
	xorl	%edi, %ecx
	movl	%ecx, 4(%eax,%edx,4)
	incl	%edx
	cmpl	%ebx, %edx
	movl	%ecx, %esi
	jl	LBB0_9
## BB#10:                               ## %.loopexit.1
                                        ##   in Loop: Header=BB0_6 Depth=1
	cmpl	$1, %ebx
	jg	LBB0_6
LBB0_11:                                ## %._crit_edge
	addl	$4, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl


.subsections_via_symbols
