	.text	
	.globl		main
main:
	li		$t0, 3
	sw		$t0, i
	li		$t0, 8
	sw		$t0, j
	li		$t0, 2
	sw		$t0, k
	lw		$t0, i
	lw		$t1, j
	lw		$t2, k
	mul		$t3, $t1, $t2
	add		$t1, $t0, $t3
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W1
	syscall	
	li		$t0, 1
	move		$a1, $t0
L1:
	beq		$zero, $a1, L2
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L1
L2:
	lw		$t0, j
	lw		$t1, i
	div		$t2, $t0, $t1
	lw		$t0, k
	add		$t1, $t2, $t0
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W2
	syscall	
	li		$t0, 1
	move		$a1, $t0
L3:
	beq		$zero, $a1, L4
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L3
L4:
	lw		$t0, k
	lw		$t1, j
	mul		$t2, $t0, $t1
	lw		$t0, i
	div		$t2, $t0
	mfhi		$t1
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W3
	syscall	
	li		$t0, 1
	move		$a1, $t0
L5:
	beq		$zero, $a1, L6
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L5
L6:
	lw		$t0, j
	lw		$t1, k
	lw		$t2, i
	move		$t3, $t1
	move		$t4, $t2
	move		$t5, $t2
	sub		$t5, $t5, 1
	beq		$zero, $t5, L9
	sub		$t4, $t4, 1
L7:
	beq		$zero, $t4, L8
	mul		$t3, $t3, $t1
	subi		$t4, $t4, 1
	j		L7
L9:
	move		$t3, $t1
L8:
	move		$t1, $t0
	move		$t2, $t3
	move		$t4, $t3
	sub		$t4, $t4, 1
	beq		$zero, $t4, L12
	sub		$t2, $t2, 1
L10:
	beq		$zero, $t2, L11
	mul		$t1, $t1, $t0
	subi		$t2, $t2, 1
	j		L10
L12:
	move		$t1, $t0
L11:
	sw		$t1, m
	lw		$t0, m
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W4
	syscall	
	li		$t0, 1
	move		$a1, $t0
L13:
	beq		$zero, $a1, L14
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L13
L14:
	li		$v0, 10
	syscall	
	.data	
	.align		4
i:	.word		0
j:	.word		0
k:	.word		0
m:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W4:	.asciiz		" = 8^2^3"
_W3:	.asciiz		" = 2*8%3"
_W2:	.asciiz		" = 8/3 + 2"
_W1:	.asciiz		" = 3+8*2"
