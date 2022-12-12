	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, _W1
	syscall	
	li		$v0, 5
	syscall	
	sw		$v0, count
L10:
	li		$t1, 0
	lw		$t0, count
	slt		$t2, $t1, $t0
	beq		$zero, $t2, L11
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
	lw		$t0, low
	lw		$t1, mid
	slt		$t3, $t0, $t1
	lw		$t1, high
	lw		$t0, mid
	slt		$t4, $t1, $t0
	sne		$t3, $t3, $zero
	sne		$t4, $t4, $zero
	and		$t0, $t3, $t4
	beq		$zero, $t0, L6
	lw		$t1, mid
	sw		$t1, temp
	lw		$t1, high
	sw		$t1, mid
	lw		$t1, temp
	sw		$t1, high
	lw		$t3, mid
	lw		$t1, low
	slt		$t4, $t3, $t1
	beq		$zero, $t4, L1
	lw		$t1, low
	sw		$t1, temp
	lw		$t1, mid
	sw		$t1, low
	lw		$t1, temp
	sw		$t1, mid
L1:
L6:
	bne		$zero, $t0, L7
	lw		$t3, mid
	lw		$t1, low
	slt		$t4, $t3, $t1
	lw		$t1, mid
	lw		$t3, high
	slt		$t5, $t1, $t3
	sne		$t4, $t4, $zero
	sne		$t5, $t5, $zero
	and		$t1, $t4, $t5
	beq		$zero, $t1, L4
	lw		$t3, low
	sw		$t3, temp
	lw		$t3, mid
	sw		$t3, low
	lw		$t3, temp
	sw		$t3, mid
	lw		$t4, high
	lw		$t3, mid
	slt		$t5, $t4, $t3
	beq		$zero, $t5, L2
	lw		$t3, mid
	sw		$t3, temp
	lw		$t3, high
	sw		$t3, mid
	lw		$t3, temp
	sw		$t3, high
L2:
L4:
	bne		$zero, $t1, L5
	lw		$t4, mid
	lw		$t3, low
	slt		$t5, $t4, $t3
	lw		$t4, high
	lw		$t3, mid
	slt		$t6, $t4, $t3
	sne		$t5, $t5, $zero
	sne		$t6, $t6, $zero
	and		$t3, $t5, $t6
	beq		$zero, $t3, L3
	lw		$t4, low
	sw		$t4, temp
	lw		$t4, high
	sw		$t4, low
	lw		$t4, temp
	sw		$t4, high
L3:
L5:
L7:
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
L8:
	beq		$zero, $a1, L9
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L8
L9:
	lw		$t0, count
	li		$t1, 1
	sub		$t3, $t0, $t1
	sw		$t3, count
	j		L10
L11:
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
