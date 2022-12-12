	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, _W1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, count
	li		$t0, 0
	sw		$t0, i
L1:
	lw		$t0, i
	lw		$t1, count
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L2
	li		$v0, 4
	la		$a0, _W2
	syscall	
	li		$v0, 5
	syscall	
	sll		$t0, $t0, 2
	sw		$v0, numbers($t0)
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L1
L2:
	li		$t0, 2
	move		$a1, $t0
L3:
	beq		$zero, $a1, L4
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L3
L4:
	li		$t0, 0
	sw		$t0, i
L7:
	lw		$t0, i
	lw		$t1, count
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L8
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t0, numbers($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$t0, 1
	move		$a1, $t0
L5:
	beq		$zero, $a1, L6
	li		$v0, 4
	la		$a0, _space
	syscall	
	subi		$a1, $a1, 1
	j		L5
L6:
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L7
L8:
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
	li		$v0, 10
	syscall	
	.data	
	.align		4
numbers:	.space		120
p:	.word		0
s:	.word		0
temp:	.word		0
i:	.word		0
count:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W2:	.asciiz		"Enter an int: "
_W1:	.asciiz		"Enter the number of ints (30 or less) in the array: "
