	.text	
	.globl		main
main:
	li		$v0, 4
	la		$a0, _W1
	syscall	
	li		$t0, 0
	sw		$t0, i
L3:
	lw		$t0, i
	li		$t1, 5
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L4
	li		$t0, 0
	sw		$t0, j
L1:
	lw		$t0, j
	li		$t1, 4
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L2
	li		$v0, 5
	syscall	
	sw		$v0, k
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t1, j
	mul		$t1, $t1, 5
	sll		$t1, $t1, 2
	add		$t0, $t0, $t1
	lw		$t4, k
	sw		$t4, twoD($t0)
	lw		$t0, j
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, j
	j		L1
L2:
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L3
L4:
	li		$t0, 0
	sw		$t0, i
L7:
	lw		$t0, i
	li		$t1, 5
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L8
	li		$t0, 0
	sw		$t0, j
	lw		$t0, i
	sll		$t0, $t0, 2
	li		$t1, 0
	sw		$t1, rowSums($t0)
L5:
	lw		$t0, j
	li		$t1, 4
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L6
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t1, i
	sll		$t1, $t1, 2
	lw		$t1, rowSums($t1)
	lw		$t4, i
	sll		$t4, $t4, 2
	lw		$t5, j
	mul		$t5, $t5, 5
	sll		$t5, $t5, 2
	add		$t4, $t4, $t5
	lw		$t4, twoD($t4)
	add		$t5, $t1, $t4
	sw		$t5, rowSums($t0)
	lw		$t0, j
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, j
	j		L5
L6:
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L7
L8:
	li		$t0, 0
	sw		$t0, j
L11:
	lw		$t0, j
	li		$t1, 4
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L12
	li		$t0, 0
	sw		$t0, i
L9:
	lw		$t0, i
	li		$t1, 5
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L10
	lw		$t0, j
	sll		$t0, $t0, 2
	lw		$t1, j
	sll		$t1, $t1, 2
	lw		$t1, colSums($t1)
	lw		$t4, i
	sll		$t4, $t4, 2
	lw		$t5, j
	mul		$t5, $t5, 5
	sll		$t5, $t5, 2
	add		$t4, $t4, $t5
	lw		$t4, twoD($t4)
	add		$t5, $t1, $t4
	sw		$t5, colSums($t0)
	lw		$t0, i
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, i
	j		L9
L10:
	lw		$t0, j
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, j
	j		L11
L12:
	li		$t0, 0
	sw		$t0, i
L21:
	lw		$t0, i
	li		$t1, 5
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L22
	li		$t0, 0
	sw		$t0, j
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t0, rowSums($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$t0, 4
	move		$a1, $t0
L13:
	beq		$zero, $a1, L14
	li		$v0, 4
	la		$a0, _space
	syscall	
	subi		$a1, $a1, 1
	j		L13
L14:
L17:
	lw		$t0, j
	li		$t1, 4
	slt		$t3, $t0, $t1
	beq		$zero, $t3, L18
	lw		$t0, i
	sll		$t0, $t0, 2
	lw		$t1, j
	mul		$t1, $t1, 5
	sll		$t1, $t1, 2
	add		$t0, $t0, $t1
	lw		$t0, twoD($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$t0, 4
	move		$a1, $t0
L15:
	beq		$zero, $a1, L16
	li		$v0, 4
	la		$a0, _space
	syscall	
	subi		$a1, $a1, 1
	j		L15
L16:
	lw		$t0, j
	li		$t1, 1
	add		$t4, $t0, $t1
	sw		$t4, j
	j		L17
L18:
	li		$t0, 1
	move		$a1, $t0
L19:
	beq		$zero, $a1, L20
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L19
L20:
	lw		$t0, i
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, i
	j		L21
L22:
	li		$t0, 0
	sw		$t0, j
	li		$t0, 4
	move		$a1, $t0
L23:
	beq		$zero, $a1, L24
	li		$v0, 4
	la		$a0, _space
	syscall	
	subi		$a1, $a1, 1
	j		L23
L24:
L27:
	lw		$t0, j
	li		$t1, 4
	slt		$t2, $t0, $t1
	beq		$zero, $t2, L28
	lw		$t0, j
	sll		$t0, $t0, 2
	lw		$t0, colSums($t0)
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$t0, 4
	move		$a1, $t0
L25:
	beq		$zero, $a1, L26
	li		$v0, 4
	la		$a0, _space
	syscall	
	subi		$a1, $a1, 1
	j		L25
L26:
	lw		$t0, j
	li		$t1, 1
	add		$t3, $t0, $t1
	sw		$t3, j
	j		L27
L28:
	li		$t0, 1
	move		$a1, $t0
L29:
	beq		$zero, $a1, L30
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L29
L30:
	li		$v0, 10
	syscall	
	.data	
	.align		4
colSums:	.space		16
rowSums:	.space		20
twoD:	.space		80
i:	.word		0
j:	.word		0
k:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W1:	.asciiz		"Enter 20 ints: "
