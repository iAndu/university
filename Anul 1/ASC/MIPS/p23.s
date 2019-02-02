.data
	x: .align 2
		.space 4
	y: .align 2
		.space 4
	z: .align 2
		.space 4
	label1: .asciiz "Introduceti x: "
	label2: .asciiz "\nIntroduceti y: "
	label3: .asciiz "\nIntroduceti z: "
	labela: .asciiz "\nValoarea expresiei: "
.text
	main:
		la $a0, label1
		li $v0, 4
		syscall

		li $v0, 5
		syscall
		move $t0, $v0
		sw $t0, x

		la $a0, label2
		li $v0, 4
		syscall

		li $v0, 5
		syscall
		move $t0, $v0
		sw $t0, y

		la $a0, label3
		li $v0, 4
		syscall

		li $v0, 5
		syscall
		move $t0, $v0
		sw $t0, z

		lw $t0, x
		jal calc

		li $t1, 0
		add $t1, $t0, $t1

		lw $t0, y
		jal calc

		add $t1, $t0, $t1

		lw $t0, z
		jal calc

		add $t1, $t0, $t1

		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t1
		li $v0, 1
		syscall

		li $v0, 10
		syscall

	calc:
		sub $t0, 1
		mulo $t0, $t0, $t0
		jr $ra