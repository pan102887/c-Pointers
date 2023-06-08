	.file	"demo.c"
	.text
	.section	.rodata
.LC0:
	.string	"sum = %d\n"
.LC1:
	.string	"str test"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	; 将%rbp的值保存到栈中，%rbp是栈帧指针
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	; 将%rsp的值赋给%rbp
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -32(%rbp)
	movl	$1, -28(%rbp)
	movl	$2, -24(%rbp)
	movl	$3, -20(%rbp)
	movl	$4, -16(%rbp)
	movl	$0, -40(%rbp)
	movl	$0, -36(%rbp)
	jmp	.L2
.L3:
	movl	-36(%rbp), %eax
	cltq
	movl	-32(%rbp,%rax,4), %eax
	addl	%eax, -40(%rbp)
	addl	$1, -36(%rbp)
.L2:
	cmpl	$4, -36(%rbp)
	jle	.L3
	movl	-40(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 12.1.0-2ubuntu1~22.04) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
