	.file	"demo.c"
	.text
	.p2align 4
	.type	set_columns, @function
set_columns:
.LFB153:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	leaq	positions(%rip), %rax
	leaq	heights(%rip), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movslq	colsOffset(%rip), %rbx
	leaq	(%rbx,%rbx,2), %rdx
	leaq	(%rax,%rdx,4), %rbp
	.p2align 4,,10
	.p2align 3
.L2:
	movl	$4, %esi
	movl	$1, %edi
	addq	$12, %rbp
	call	GetRandomValue@PLT
	pxor	%xmm0, %xmm0
	movl	$32, %esi
	xorl	%edi, %edi
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, (%r12,%rbx,4)
	movss	renderBound(%rip), %xmm0
	subss	.LC0(%rip), %xmm0
	movss	%xmm0, 8(%rsp)
	call	GetRandomValue@PLT
	pxor	%xmm0, %xmm0
	movl	$15, %esi
	movss	.LC1(%rip), %xmm1
	mulss	(%r12,%rbx,4), %xmm1
	cvtsi2ssl	%eax, %xmm0
	addss	8(%rsp), %xmm0
	movl	$-15, %edi
	addq	$1, %rbx
	unpcklps	%xmm1, %xmm0
	movlps	%xmm0, 8(%rsp)
	call	GetRandomValue@PLT
	movq	8(%rsp), %xmm0
	movlps	%xmm0, -12(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movl	colsOffset(%rip), %eax
	addl	$19, %eax
	movss	%xmm0, -4(%rbp)
	cmpl	%ebx, %eax
	jge	.L2
	addq	$16, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE153:
	.size	set_columns, .-set_columns
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC17:
	.string	"raylib [core] example - 3d camera first person"
	.align 8
.LC29:
	.string	"First person camera default controls:"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC30:
	.string	"- Move with keys: W, A, S, D"
.LC31:
	.string	"- Mouse move to look around"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB162:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$450, %esi
	movl	$800, %edi
	leaq	.LC17(%rip), %rdx
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movdqa	.LC7(%rip), %xmm0
	movaps	%xmm0, colors(%rip)
	movdqa	.LC8(%rip), %xmm0
	movaps	%xmm0, 16+colors(%rip)
	movdqa	.LC9(%rip), %xmm0
	movaps	%xmm0, 32+colors(%rip)
	movdqa	.LC10(%rip), %xmm0
	movaps	%xmm0, 48+colors(%rip)
	movdqa	.LC11(%rip), %xmm0
	movaps	%xmm0, 64+colors(%rip)
	movdqa	.LC12(%rip), %xmm0
	movaps	%xmm0, 80+colors(%rip)
	movdqa	.LC13(%rip), %xmm0
	movaps	%xmm0, 96+colors(%rip)
	movdqa	.LC14(%rip), %xmm0
	movaps	%xmm0, 112+colors(%rip)
	movdqa	.LC15(%rip), %xmm0
	movaps	%xmm0, 128+colors(%rip)
	movdqa	.LC16(%rip), %xmm0
	movaps	%xmm0, 144+colors(%rip)
	call	InitWindow@PLT
	movaps	.LC18(%rip), %xmm0
	movq	.LC20(%rip), %rax
	movl	$0, 40+camera(%rip)
	movaps	%xmm0, camera(%rip)
	movaps	.LC19(%rip), %xmm0
	movq	%rax, 32+camera(%rip)
	movaps	%xmm0, 16+camera(%rip)
	call	set_columns
	movl	colsOffset(%rip), %eax
	subq	$48, %rsp
	.cfi_def_cfa_offset 176
	movdqa	camera(%rip), %xmm5
	movl	$3, %edi
	leal	20(%rax), %edx
	movups	%xmm5, (%rsp)
	movdqa	16+camera(%rip), %xmm5
	movslq	%edx, %rax
	movl	%edx, %ecx
	imulq	$1717986919, %rax, %rax
	sarl	$31, %ecx
	movups	%xmm5, 16(%rsp)
	sarq	$36, %rax
	subl	%ecx, %eax
	leal	(%rax,%rax,4), %eax
	sall	$3, %eax
	subl	%eax, %edx
	movq	32+camera(%rip), %rax
	movl	%edx, colsOffset(%rip)
	movq	%rax, 32(%rsp)
	movl	40+camera(%rip), %eax
	movl	%eax, 40(%rsp)
	call	SetCameraMode@PLT
	addq	$48, %rsp
	.cfi_def_cfa_offset 128
	movl	$60, %edi
	call	SetTargetFPS@PLT
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L50:
	pxor	%xmm0, %xmm0
	movss	%xmm3, 24(%rsp)
	cvtss2sd	%xmm1, %xmm0
	movsd	.LC23(%rip), %xmm1
	movss	%xmm2, 20(%rsp)
	movss	%xmm6, 16(%rsp)
	subsd	%xmm0, %xmm1
.L47:
	pxor	%xmm0, %xmm0
	call	fmax@PLT
	movss	16(%rsp), %xmm6
	movss	20(%rsp), %xmm2
	pxor	%xmm5, %xmm5
	movss	24(%rsp), %xmm3
	cvtsd2ss	%xmm0, %xmm5
.L20:
	movss	8+camera(%rip), %xmm4
	pxor	%xmm1, %xmm1
	comiss	(%rsp), %xmm6
	movss	%xmm5, 4+manuBoundFactor(%rip)
	cvtss2sd	%xmm4, %xmm1
	mulsd	.LC25(%rip), %xmm1
	cvtsd2ss	%xmm1, %xmm1
	jbe	.L44
	pxor	%xmm0, %xmm0
	movss	%xmm3, 28(%rsp)
	cvtss2sd	%xmm1, %xmm0
	movsd	.LC23(%rip), %xmm1
	movss	%xmm5, 24(%rsp)
	movss	%xmm4, 20(%rsp)
	subsd	%xmm0, %xmm1
	movss	%xmm2, 16(%rsp)
.L48:
	pxor	%xmm0, %xmm0
	call	fmax@PLT
	movss	28(%rsp), %xmm3
	movss	16(%rsp), %xmm2
	cvtsd2ss	%xmm0, %xmm0
	movss	20(%rsp), %xmm4
	movss	24(%rsp), %xmm5
	mulss	%xmm0, %xmm3
.L24:
	mulss	4(%rsp), %xmm2
	movss	%xmm0, 8+manuBoundFactor(%rip)
	movss	(%rsp), %xmm0
	addss	%xmm3, %xmm4
	movq	16+camera(%rip), %xmm1
	mulss	manuBoundFactor(%rip), %xmm0
	movl	$-657931, %edi
	mulss	%xmm5, %xmm2
	movaps	%xmm2, %xmm5
	addss	8(%rsp), %xmm2
	unpcklps	%xmm3, %xmm5
	addps	%xmm1, %xmm5
	xorps	%xmm1, %xmm1
	addps	%xmm1, %xmm5
	movss	camera(%rip), %xmm1
	addss	%xmm0, %xmm1
	addss	12+camera(%rip), %xmm0
	movlps	%xmm5, 16+camera(%rip)
	unpcklps	%xmm0, %xmm4
	movaps	%xmm1, %xmm0
	unpcklps	%xmm2, %xmm0
	movlhps	%xmm4, %xmm0
	addps	.LC26(%rip), %xmm0
	movaps	%xmm0, camera(%rip)
	call	ClearBackground@PLT
	cvttss2sil	camera(%rip), %edx
	pxor	%xmm1, %xmm1
	movss	renderBound(%rip), %xmm0
	movss	.LC0(%rip), %xmm6
	movss	%xmm6, (%rsp)
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm0, %xmm1
	ja	.L40
.L26:
	movq	32+camera(%rip), %rax
	subq	$48, %rsp
	.cfi_def_cfa_offset 176
	movdqa	camera(%rip), %xmm6
	movabsq	$4755801207602151424, %rbx
	movdqa	16+camera(%rip), %xmm7
	leaq	colors(%rip), %r13
	leaq	heights(%rip), %rbp
	movq	%rax, 32(%rsp)
	movl	40+camera(%rip), %eax
	leaq	positions(%rip), %r12
	movups	%xmm6, (%rsp)
	movups	%xmm7, 16(%rsp)
	movl	%eax, 40(%rsp)
	call	BeginMode3D@PLT
	addq	$48, %rsp
	.cfi_def_cfa_offset 128
	movl	12(%rsp), %esi
	cmpl	$1, colsOffset(%rip)
	sbbl	%eax, %eax
	pxor	%xmm3, %xmm3
	movq	%rbx, %xmm2
	xorl	%edx, %edx
	andl	$-120, %eax
	cvtss2sd	renderBound(%rip), %xmm3
	subsd	.LC27(%rip), %xmm3
	movq	$0, 56(%rsp)
	subl	$56, %eax
	movss	60(%rsp), %xmm1
	movb	%al, %dl
	movb	%al, %dh
	movzbl	%al, %eax
	cvtsd2ss	%xmm3, %xmm3
	movss	%xmm3, 52(%rsp)
	movw	%dx, %si
	sall	$16, %eax
	movq	52(%rsp), %xmm0
	movss	%xmm3, 4(%rsp)
	andl	$-16711681, %esi
	movl	%esi, %r14d
	orl	%eax, %r14d
	movl	%r14d, %edi
	orl	$-16777216, %edi
	movl	%edi, 12(%rsp)
	call	DrawPlane@PLT
	movss	4(%rsp), %xmm3
	addss	(%rsp), %xmm3
	movq	$0, 44(%rsp)
	cmpl	$1, colsOffset(%rip)
	movss	48(%rsp), %xmm1
	movq	%rbx, %xmm2
	sbbl	%eax, %eax
	xorl	%edx, %edx
	xorl	%ebx, %ebx
	andl	$120, %eax
	movss	%xmm3, 40(%rsp)
	movq	40(%rsp), %xmm0
	addl	$80, %eax
	movb	%al, %dl
	movb	%al, %dh
	movzbl	%al, %eax
	movw	%dx, %r15w
	sall	$16, %eax
	andl	$-16711681, %r15d
	orl	%eax, %r15d
	orl	$-16777216, %r15d
	movl	%r15d, %edi
	call	DrawPlane@PLT
	movss	.LC28(%rip), %xmm2
	.p2align 4,,10
	.p2align 3
.L30:
	movslq	%ebx, %rax
	movss	0(%rbp,%rbx,4), %xmm3
	movaps	%xmm2, %xmm4
	movl	0(%r13,%rax,4), %edi
	leaq	(%rax,%rax,2), %rax
	leaq	(%r12,%rax,4), %r14
	movq	(%r14), %xmm0
	movss	8(%r14), %xmm1
	call	DrawCube@PLT
	movss	0(%rbp,%rbx,4), %xmm3
	movq	(%r14), %xmm0
	movl	$-13164098, %edi
	movss	.LC28(%rip), %xmm2
	movss	8(%r14), %xmm1
	addq	$1, %rbx
	movaps	%xmm2, %xmm4
	call	DrawCubeWires@PLT
	cmpq	$40, %rbx
	movss	.LC28(%rip), %xmm2
	jne	.L30
	call	EndMode3D@PLT
	movss	.LC1(%rip), %xmm0
	movl	$-16538, %edi
	call	Fade@PLT
	movl	$70, %ecx
	movl	$220, %edx
	movl	$10, %esi
	movl	%eax, %r8d
	movl	$10, %edi
	call	DrawRectangle@PLT
	movl	$-952064, %r8d
	movl	$70, %ecx
	movl	$220, %edx
	movl	$10, %esi
	movl	$10, %edi
	call	DrawRectangleLines@PLT
	movl	$-16777216, %r8d
	movl	$10, %ecx
	movl	$20, %edx
	movl	$20, %esi
	leaq	.LC29(%rip), %rdi
	call	DrawText@PLT
	movl	$-11513776, %r8d
	movl	$10, %ecx
	movl	$40, %edx
	movl	$40, %esi
	leaq	.LC30(%rip), %rdi
	call	DrawText@PLT
	movl	$-11513776, %r8d
	movl	$10, %ecx
	movl	$60, %edx
	movl	$40, %esi
	leaq	.LC31(%rip), %rdi
	call	DrawText@PLT
	call	EndDrawing@PLT
.L7:
	call	WindowShouldClose@PLT
	testb	%al, %al
	jne	.L49
	call	BeginDrawing@PLT
	movl	$83, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	je	.L8
.L10:
	pxor	%xmm7, %xmm7
	movss	.LC2(%rip), %xmm0
	movss	%xmm7, (%rsp)
.L9:
	movl	$65, %edi
	movss	%xmm0, manuY(%rip)
	call	IsKeyDown@PLT
	testb	%al, %al
	je	.L13
.L15:
	movss	.LC6(%rip), %xmm7
	movss	.LC5(%rip), %xmm3
	movss	.LC3(%rip), %xmm6
	movss	%xmm7, 4(%rsp)
.L14:
	movss	4+camera(%rip), %xmm7
	pxor	%xmm1, %xmm1
	movss	manuY(%rip), %xmm2
	comiss	(%rsp), %xmm2
	cvtss2sd	%xmm7, %xmm1
	subsd	.LC21(%rip), %xmm1
	movss	%xmm7, 8(%rsp)
	mulsd	.LC22(%rip), %xmm1
	cvtsd2ss	%xmm1, %xmm1
	ja	.L50
	movss	(%rsp), %xmm5
	comiss	%xmm2, %xmm5
	ja	.L51
	movss	.LC2(%rip), %xmm5
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L44:
	movss	(%rsp), %xmm7
	movss	.LC2(%rip), %xmm0
	comiss	%xmm6, %xmm7
	jbe	.L24
	cvtss2sd	%xmm1, %xmm1
	movss	%xmm3, 28(%rsp)
	addsd	.LC23(%rip), %xmm1
	movss	%xmm5, 24(%rsp)
	movss	%xmm4, 20(%rsp)
	movss	%xmm2, 16(%rsp)
	jmp	.L48
.L13:
	movl	$263, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L15
	movl	$324, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L15
	movl	$68, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	je	.L16
.L17:
	movss	.LC6(%rip), %xmm6
	movss	%xmm6, 4(%rsp)
	movaps	%xmm6, %xmm3
	movss	.LC2(%rip), %xmm6
	jmp	.L14
.L8:
	movl	$264, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L10
	movl	$322, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L10
	movl	$87, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	je	.L11
.L12:
	pxor	%xmm7, %xmm7
	movss	.LC3(%rip), %xmm0
	movss	%xmm7, (%rsp)
	jmp	.L9
.L40:
	addss	%xmm6, %xmm0
	movss	%xmm0, renderBound(%rip)
	call	set_columns
	movl	colsOffset(%rip), %eax
	leal	20(%rax), %edx
	movslq	%edx, %rax
	movl	%edx, %ecx
	imulq	$1717986919, %rax, %rax
	sarl	$31, %ecx
	sarq	$36, %rax
	subl	%ecx, %eax
	leal	(%rax,%rax,4), %eax
	sall	$3, %eax
	subl	%eax, %edx
	movl	%edx, colsOffset(%rip)
	jmp	.L26
.L51:
	cvtss2sd	%xmm1, %xmm1
	movss	%xmm3, 24(%rsp)
	addsd	.LC23(%rip), %xmm1
	movss	%xmm2, 20(%rsp)
	movss	%xmm6, 16(%rsp)
	jmp	.L47
.L49:
	call	CloseWindow@PLT
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L16:
	.cfi_restore_state
	movl	$262, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L17
	movl	$326, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L17
	movss	(%rsp), %xmm6
	movss	.LC6(%rip), %xmm7
	movaps	%xmm6, %xmm3
	movss	%xmm7, 4(%rsp)
	jmp	.L14
.L11:
	movl	$265, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L12
	movl	$328, %edi
	call	IsKeyDown@PLT
	testb	%al, %al
	jne	.L12
	movl	$0x00000000, (%rsp)
	pxor	%xmm0, %xmm0
	jmp	.L9
	.cfi_endproc
.LFE162:
	.size	main, .-main
	.local	manuBoundFactor
	.comm	manuBoundFactor,12,8
	.local	manuY
	.comm	manuY,4,4
	.data
	.align 4
	.type	renderBound, @object
	.size	renderBound, 4
renderBound:
	.long	1098907648
	.local	colsOffset
	.comm	colsOffset,4,4
	.local	colors
	.comm	colors,160,32
	.local	positions
	.comm	positions,480,32
	.local	heights
	.comm	heights,160,32
	.local	camera
	.comm	camera,44,32
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1098907648
	.align 4
.LC1:
	.long	1056964608
	.set	.LC2,.LC19+12
	.align 4
.LC3:
	.long	-1082130432
	.align 4
.LC5:
	.long	-1110651699
	.align 4
.LC6:
	.long	1036831949
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC7:
	.byte	27
	.byte	35
	.byte	22
	.byte	-1
	.byte	19
	.byte	11
	.byte	6
	.byte	-1
	.byte	30
	.byte	43
	.byte	44
	.byte	-1
	.byte	30
	.byte	28
	.byte	39
	.byte	-1
	.align 16
.LC8:
	.byte	31
	.byte	30
	.byte	26
	.byte	-1
	.byte	37
	.byte	41
	.byte	34
	.byte	-1
	.byte	46
	.byte	47
	.byte	42
	.byte	-1
	.byte	34
	.byte	20
	.byte	21
	.byte	-1
	.align 16
.LC9:
	.byte	44
	.byte	31
	.byte	24
	.byte	-1
	.byte	43
	.byte	45
	.byte	35
	.byte	-1
	.byte	45
	.byte	30
	.byte	28
	.byte	-1
	.byte	52
	.byte	59
	.byte	49
	.byte	-1
	.align 16
.LC10:
	.byte	43
	.byte	36
	.byte	41
	.byte	-1
	.byte	68
	.byte	60
	.byte	62
	.byte	-1
	.byte	70
	.byte	59
	.byte	62
	.byte	-1
	.byte	62
	.byte	64
	.byte	62
	.byte	-1
	.align 16
.LC11:
	.byte	52
	.byte	40
	.byte	36
	.byte	-1
	.byte	59
	.byte	65
	.byte	71
	.byte	-1
	.byte	76
	.byte	72
	.byte	59
	.byte	-1
	.byte	54
	.byte	63
	.byte	69
	.byte	-1
	.align 16
.LC12:
	.byte	67
	.byte	79
	.byte	85
	.byte	-1
	.byte	79
	.byte	66
	.byte	57
	.byte	-1
	.byte	69
	.byte	81
	.byte	65
	.byte	-1
	.byte	67
	.byte	70
	.byte	62
	.byte	-1
	.align 16
.LC13:
	.byte	96
	.byte	87
	.byte	82
	.byte	-1
	.byte	61
	.byte	80
	.byte	81
	.byte	-1
	.byte	95
	.byte	105
	.byte	109
	.byte	-1
	.byte	54
	.byte	59
	.byte	68
	.byte	-1
	.align 16
.LC14:
	.byte	95
	.byte	93
	.byte	102
	.byte	-1
	.byte	92
	.byte	77
	.byte	72
	.byte	-1
	.byte	88
	.byte	79
	.byte	89
	.byte	-1
	.byte	65
	.byte	69
	.byte	80
	.byte	-1
	.align 16
.LC15:
	.byte	80
	.byte	70
	.byte	70
	.byte	-1
	.byte	64
	.byte	81
	.byte	78
	.byte	-1
	.byte	122
	.byte	111
	.byte	124
	.byte	-1
	.byte	118
	.byte	126
	.byte	109
	.byte	-1
	.align 16
.LC16:
	.byte	83
	.byte	82
	.byte	96
	.byte	-1
	.byte	102
	.byte	108
	.byte	109
	.byte	-1
	.byte	92
	.byte	95
	.byte	95
	.byte	-1
	.byte	118
	.byte	115
	.byte	-126
	.byte	-1
	.align 16
.LC18:
	.long	0
	.long	1082130432
	.long	0
	.long	1082130432
	.align 16
.LC19:
	.long	1082130432
	.long	0
	.long	0
	.long	1065353216
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC20:
	.long	0
	.long	1114636288
	.align 8
.LC21:
	.long	0
	.long	1074790400
	.align 8
.LC22:
	.long	-1717986918
	.long	1071225241
	.align 8
.LC23:
	.long	0
	.long	1072693248
	.align 8
.LC25:
	.long	-1717986918
	.long	1069128089
	.section	.rodata.cst16
	.align 16
.LC26:
	.long	1031127695
	.long	0
	.long	0
	.long	1031127695
	.section	.rodata.cst8
	.align 8
.LC27:
	.long	-1717986918
	.long	1075419545
	.section	.rodata.cst4
	.align 4
.LC28:
	.long	1073741824
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
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
