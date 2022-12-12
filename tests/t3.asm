	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, _W1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, i
	li		$v0, 5
	syscall	
	sw		$v0, j
	li		$v0, 5
	syscall	
	sw		$v0, k
	li		$v0, 5
	syscall	
	sw		$v0, m
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
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _space
	syscall	
	lw		$t1, j
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _space
	syscall	
	lw		$t2, k
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _space
	syscall	
	lw		$t3, m
	add		$a0, $t3, $zero
	li		$v0, 1
	syscall	
	li		$t0, 8
	move		$a1, $t0
L3:
	beq		$zero, $a1, L4
	li		$v0, 4
	la		$a0, _space
	syscall	
	subi		$a1, $a1, 1
	j		L3
L4:
	lw		$t0, i
	lw		$t1, j
	move		$t2, $t0
	move		$t3, $t1
	move		$t4, $t1
	sub		$t4, $t4, 1
	beq		$zero, $t4, L7
	sub		$t3, $t3, 1
L5:
	beq		$zero, $t3, L6
	mul		$t2, $t2, $t0
	subi		$t3, $t3, 1
	j		L5
L7:
	move		$t2, $t0
L6:
	lw		$t0, k
	mul		$t1, $t2, $t0
	lw		$t0, m
	add		$t2, $t1, $t0
	add		$a0, $t2, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W2
	syscall	
	li		$t0, 8
	move		$a1, $t0
L8:
	beq		$zero, $a1, L9
	li		$v0, 4
	la		$a0, _space
	syscall	
	subi		$a1, $a1, 1
	j		L8
L9:
	lw		$t0, m
	lw		$t1, k
	lw		$t2, i
	lw		$t3, j
	move		$t4, $t2
	move		$t5, $t3
	move		$t6, $t3
	sub		$t6, $t6, 1
	beq		$zero, $t6, L12
	sub		$t5, $t5, 1
L10:
	beq		$zero, $t5, L11
	mul		$t4, $t4, $t2
	subi		$t5, $t5, 1
	j		L10
L12:
	move		$t4, $t2
L11:
	mul		$t2, $t1, $t4
	add		$t1, $t0, $t2
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W3
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
_W3:	.asciiz		" = m+k*i^j"
_W2:	.asciiz		" = i^j*k+m"
_W1:	.asciiz		"Enter 4 integers. The second integer must be positive: "
