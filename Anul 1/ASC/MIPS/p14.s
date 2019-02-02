.data
	label1: .asciiz "Introduceti primul numar: "
	label2: .asciiz "Introduceti al doilea numar: "
	labelx: .asciiz "Variabila x este: "
	labely: .asciiz "Variabila y este: "
	x: .align 2
		.space 4
	y: .align 2
		.space 4
.text
	main:
		la $a0, label1
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t1, $v0

		la $a0, label2
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t2, $v0
		blt $t1, $t2, save1
		b save2

	save1:
		la $t0, x
		sw $t1, ($t0)
		la $t0, y
		sw $t2, ($t0)
		b exit

	save2:
		la $t0, x
		sw $t2, ($t0)
		la $t0, y
		sw $t1, ($t0)
		b exit

	exit:
		la $a0, labelx
		li $v0, 4
		syscall
		lw $a0, x
		li $v0, 1
		syscall

		la $a0, labely
		li $v0, 4
		syscall
		lw $a0, y
		li $v0, 1
		syscall

		li $v0, 10
		syscall