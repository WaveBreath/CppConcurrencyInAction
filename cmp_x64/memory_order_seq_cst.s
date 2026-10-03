_Z9incrementPSt6atomicIiEP11read_values:
.LVL22:
.LFB11914:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rsi, %rbx
	jmp	.L12
.LVL23:
	.p2align 4,,10
	.p2align 3
.L13:
	call	sched_yield@PLT
.LVL24:
.L12:
	movl	go(%rip), %eax
.LVL25:
	testl	%eax, %eax
	je	.L13
	xorl	%ebp, %ebp
.LVL26:
	.p2align 4,,10
	.p2align 3
.L14:
	addl	$1, %ebp
.LVL27:
	movl	x(%rip), %eax
.LVL28:
	movl	%eax, (%rbx)
.LVL29:
	movl	y(%rip), %eax
.LVL30:
	movl	%eax, 4(%rbx)
.LVL31:
	movl	z(%rip), %eax
.LVL32:
	movl	%eax, 8(%rbx)
.LVL33:
	movl	%ebp, %eax
	xchgl	(%r12), %eax
.LVL34:
	addq	$12, %rbx
	call	sched_yield@PLT
.LVL35:
	cmpl	$100, %ebp
	jne	.L14
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
.LVL36:
	popq	%r12
	.cfi_def_cfa_offset 8
.LVL37:
	ret
	.cfi_endproc