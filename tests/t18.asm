	.text	
	.globl		main
main:
	li		$t0, 1
	sw		$t0, x
	li		$t0, 0
	sw		$t0, y
	lw		$t0, x
	lw		$t1, y
	sne		$t0, $t0, $zero
	sne		$t1, $t1, $zero
	and		$t2, $t0, $t1
	sw		$t2, z
	lw		$t0, z
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
	lw		$t0, x
	lw		$t1, y
	sne		$t0, $t0, $zero
	sne		$t1, $t1, $zero
	or		$t2, $t0, $t1
	sw		$t2, z
	lw		$t0, z
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
	lw		$t0, x
	beq		$zero, $t0, L5
	li		$t0, 0
	j		L6
L5:
	li		$t0, 1
L6:
	sw		$t0, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W3
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
	lw		$t0, x
	lw		$t1, y
	sne		$t0, $t0, $zero
	sne		$t1, $t1, $zero
	and		$t2, $t0, $t1
	beq		$zero, $t2, L9
	li		$t2, 0
	j		L10
L9:
	li		$t2, 1
L10:
	sw		$t2, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W4
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
	lw		$t0, x
	beq		$zero, $t0, L13
	li		$t0, 0
	j		L14
L13:
	li		$t0, 1
L14:
	lw		$t1, y
	beq		$zero, $t1, L15
	li		$t1, 0
	j		L16
L15:
	li		$t1, 1
L16:
	sne		$t0, $t0, $zero
	sne		$t1, $t1, $zero
	or		$t2, $t0, $t1
	sw		$t2, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W5
	syscall	
	li		$t0, 1
	move		$a1, $t0
L17:
	beq		$zero, $a1, L18
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L17
L18:
	lw		$t0, x
	beq		$zero, $t0, L19
	li		$t0, 0
	j		L20
L19:
	li		$t0, 1
L20:
	beq		$zero, $t0, L21
	li		$t0, 0
	j		L22
L21:
	li		$t0, 1
L22:
	sw		$t0, z
	lw		$t0, z
	add		$a0, $t0, $zero
	li		$v0, 1
	syscall	
	li		$v0, 4
	la		$a0, _W6
	syscall	
	li		$t0, 1
	move		$a1, $t0
L23:
	beq		$zero, $a1, L24
	li		$v0, 4
	la		$a0, _nl
	syscall	
	subi		$a1, $a1, 1
	j		L23
L24:
	li		$v0, 10
	syscall	
	.data	
	.align		4
x:	.word		0
y:	.word		0
z:	.word		0
_nl:	.asciiz		"\n"
_space:	.asciiz		" "
_true:	.asciiz		"true"
_false:	.asciiz		"false"
_W6:	.asciiz		" =  !!x"
_W5:	.asciiz		" =  !x || !y"
_W4:	.asciiz		" =  !(x && y)"
_W3:	.asciiz		" =  !x"
_W2:	.asciiz		" =  x || y"
_W1:	.asciiz		" =  x && y"
