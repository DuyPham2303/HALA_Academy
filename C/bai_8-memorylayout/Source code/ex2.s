	.file	"ex2.c"
	.text
.lcomm p1,8,8
	.globl	p2
	.bss
	.align 8
p2:
	.space 8
	.globl	p3
	.data
	.align 8
p3:
	.long	0
	.long	1
	.globl	a
	.bss
	.align 4
a:
	.space 4
	.globl	b
	.align 4
b:
	.space 4
.lcomm global,4,4
.lcomm global_2,4,4
	.text
	.globl	test
	.def	test;	.scl	2;	.type	32;	.endef
	.seh_proc	test
test:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
.lcomm local_2.1,4,4
.lcomm local.0,4,4
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
