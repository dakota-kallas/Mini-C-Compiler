	.text	
	.globl		main
main:
	li		$t0, 7
	sw		$t0, i
	li		$t0, 20
	sw		$t0, j
	lw		$t0, i
	lw		$t1, j
	add		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
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
	lw		$t0, i
	lw		$t1, j
	sub		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
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
	lw		$t0, i
	lw		$t1, j
	mul		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
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
	lw		$t0, i
	lw		$t1, j
	div		$t2, $t0, $t1
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W4
	syscall	
	li		$t0, 1
	move		$a1, $t0
L7:
	beq		$zero, $a1, L8
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L7
L8:
	lw		$t0, i
	lw		$t1, j
	div		$t0, $t1
	mfhi		$t2
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W5
	syscall	
	li		$t0, 1
	move		$a1, $t0
L9:
	beq		$zero, $a1, L10
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L9
L10:
	lw		$t0, i
	subu		$t1, $zero, $t0
	sw		$t1, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W6
	syscall	
	li		$t0, 1
	move		$a1, $t0
L11:
	beq		$zero, $a1, L12
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L11
L12:
	lw		$t0, i
	li		$t1, 3
	move		$t2, $t0
	move		$t3, $t1
	move		$t4, $t1
	sub		$t4, $t4, 1
	beq		$zero, $t4, L15
	sub		$t3, $t3, 1
L13:
	beq		$zero, $t3, L14
	mul		$t2, $t2, $t0
	subi		$t3, $t3, 1
	j		L13
L15:
	move		$t2, $t0
L14:
	sw		$t2, k
	lw		$t0, k
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W7
	syscall	
	li		$t0, 1
	move		$a1, $t0
L16:
	beq		$zero, $a1, L17
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L16
L17:
	li		$v0, 10
	syscall	
	.data	
	.align		4
i:	.word		0
j:	.word		0
k:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W7:	.asciiz		" = 7^3"
_W6:	.asciiz		" = -7"
_W5:	.asciiz		" = 7%20"
_W4:	.asciiz		" = 7/20"
_W3:	.asciiz		" = 7*20"
_W2:	.asciiz		" = 7-20"
_W1:	.asciiz		" = 7+20"
