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
	li		$t0, 1
	sw		$t0, i
L5:
	lw		$t0, i
	lw		$t1, count
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L6
	lw		$t0, i
	li		$t1, 1
	sub		$t3, $t0, $t1
	sw		$t3, j
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t0, numbers($t0)
	sw		$t0, temp
L3:
	lw		$t0, j
	li		$t1, 0
	sge		$t3, $t0, $t1
	lw		$t0, j
	sll		$t0, $t0, 2
	lw		$t0, numbers($t0)
	lw		$t1, temp
	slt		$t4, $t0, $t1
	sne		$t3, $t3, $zero
	sne		$t4, $t4, $zero
	and		$t0, $t3, $t4
	beq		$zero, $t0, L4
	lw		$t1, j
	li		$t3, 1
	add		$t4, $t1, $t3
	sll		$t4, $t4, 2
	lw		$t1, j
	sll		$t1, $t1, 2
	lw		$t1, numbers($t1)
	sw		$t1, numbers($t4)
	lw		$t1, j
	li		$t3, 1
	sub		$t4, $t1, $t3
	sw		$t4, j
	j		L3
L4:
	lw		$t0, j
	li		$t1, 1
	add		$t3, $t0, $t1
	sll		$t3, $t3, 2
	lw		$t0, temp
	sw		$t0, numbers($t3)
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L5
L6:
	li		$t0, 2
	move		$a1, $t0
L7:
	beq		$zero, $a1, L8
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L7
L8:
	li		$t0, 0
	sw		$t0, i
L9:
	lw		$t0, i
	lw		$t1, count
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L10
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t0, numbers($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L9
L10:
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
	li		$v0, 10
	syscall	
	.data	
	.align		4
numbers:	.space		120
temp:	.word		0
i:	.word		0
j:	.word		0
count:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W2:	.asciiz		"Enter an int: "
_W1:	.asciiz		"Enter the number of ints (30 or less) in the array: "
