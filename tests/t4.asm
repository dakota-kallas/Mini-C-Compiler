	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, _W1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, start
	li		$v0, 5
	syscall	
	sw		$v0, end
	li		$v0, 5
	syscall	
	sw		$v0, inc
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
	lw		$t0, start
	sw		$t0, current
L5:
	lw		$t0, current
	lw		$t1, end
	sle		$t2, $t0, $t1
	beq		$zero, $t2, L6
	lw		$t0, current
	li		$t1, 32
	sub		$t3, $t0, $t1
	li		$t0, 5
	mul		$t1, $t3, $t0
	li		$t0, 9
	div		$t3, $t1, $t0
	sw		$t3, c
	lw		$t0, current
	li		$t1, 460
	add		$t3, $t0, $t1
	li		$t0, 5
	mul		$t1, $t3, $t0
	li		$t0, 9
	div		$t3, $t1, $t0
	sw		$t3, k
	lw		$t0, current
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _space
	syscall	
	lw		$t1, c
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _space
	syscall	
	lw		$t3, k
	add		$a0, $t3, $zero
	li		$v0, 1
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
	lw		$t0, current
	lw		$t1, inc
	add		$t3, $t0, $t1
	sw		$t3, current
	j		L5
L6:
	li		$v0, 10
	syscall	
	.data	
	.align		4
start:	.word		0
end:	.word		0
inc:	.word		0
c:	.word		0
current:	.word		0
k:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W1:	.asciiz		"Enter three integers: Starting temp, ending temp and a positive increment: "
