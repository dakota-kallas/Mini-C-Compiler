	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, _W1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, count
L6:
	li		$t1, 0
	lw		$t0, count
	slt		$t2, $t1, $t0
	beq		$zero, $t2, L7
	li		$v0, 4
	la		$a0, _W2
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, low
	li		$v0, 5
	syscall	
	sw		$v0, mid
	li		$v0, 5
	syscall	
	sw		$v0, high
	lw		$t1, mid
	lw		$t0, low
	slt		$t3, $t1, $t0
	beq		$zero, $t3, L1
	lw		$t0, low
	sw		$t0, temp
	lw		$t0, mid
	sw		$t0, low
	lw		$t0, temp
	sw		$t0, mid
L1:
	lw		$t1, high
	lw		$t0, low
	slt		$t3, $t1, $t0
	beq		$zero, $t3, L2
	lw		$t0, low
	sw		$t0, temp
	lw		$t0, high
	sw		$t0, low
	lw		$t0, temp
	sw		$t0, high
L2:
	lw		$t1, high
	lw		$t0, mid
	slt		$t3, $t1, $t0
	beq		$zero, $t3, L3
	lw		$t0, mid
	sw		$t0, temp
	lw		$t0, high
	sw		$t0, mid
	lw		$t0, temp
	sw		$t0, high
L3:
	lw		$t0, low
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _space
	syscall	
	lw		$t1, mid
	add		$a0, $t1, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _space
	syscall	
	lw		$t3, high
	add		$a0, $t3, $zero
	li		$v0, 1
	syscall	
	li		$t0, 1
	move		$a1, $t0
L4:
	beq		$zero, $a1, L5
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L4
L5:
	lw		$t0, count
	li		$t1, 1
	sub		$t3, $t0, $t1
	sw		$t3, count
	j		L6
L7:
	li		$v0, 10
	syscall	
	.data	
	.align		4
low:	.word		0
high:	.word		0
mid:	.word		0
temp:	.word		0
count:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W2:	.asciiz		"Enter three integers: "
_W1:	.asciiz		"Enter the number of triples to be processed: "
