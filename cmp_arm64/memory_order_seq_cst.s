_Z9incrementPSt6atomicIiEP11read_values:
.LVL23:
.LFB11906:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -48
	.cfi_offset 20, -40
	mov	x19, x1
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -32
	.cfi_offset 22, -24
	adrp	x21, .LANCHOR0
	mov	x22, x0
	add	x20, x21, :lo12:.LANCHOR0
	stp	x23, x24, [sp, 48]
	.cfi_offset 23, -16
	.cfi_offset 24, -8
	b	.L12
.LVL24:
	.p2align 2,,3
.L13:
	bl	sched_yield
.LVL25:
.L12:
	ldar	w0, [x20]
	.LVL26:
	cbz	w0, .L13
	add	x21, x21, :lo12:.LANCHOR0
	mov	w20, 0
	add	x24, x21, 8
	add	x23, x21, 16
	add	x21, x21, 24
.LVL27:
	.p2align 3,,7
.L14:
	ldar	w1, [x24]
.LVL28:
	str	w1, [x19]
	.LVL29:
	ldar	w1, [x23]
.LVL30:
	str	w1, [x19, 4]
	.LVL31:
	ldar	w1, [x21]
.LVL32:
	add	w20, w20, 1
.LVL33:
	str	w1, [x19, 8]
	.LVL34:
	stlr	w20, [x22]
.LVL35:
	bl	sched_yield
.LVL36:
	add	x19, x19, 12
	cmp	w20, 100
	bne	.L14
	ldp	x19, x20, [sp, 16]
.LVL37:
	ldp	x21, x22, [sp, 32]
.LVL38:
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE11906:
	.size	_Z9incrementPSt6atomicIiEP11read_values, .-_Z9incrementPSt6atomicIiEP11read_values