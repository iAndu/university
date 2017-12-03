.data
	labelx: .asciiz "Introduceti x: "
	labely: .asciiz "Introduceti y: "
	labela: .asciiz "Rezultatul ecuatiei x * 8 - [y / 16] este: "
.text
	main:
		la $a0, labelx
		li $v0, 4
		syscall

		li $v0, 5
		syscall
		move $t1, $v0

		li $t2, 8
		mulo $t1, $t1, $t2

		la $a0, labely
		li $v0, 4
		syscall

		li $v0, 5
		syscall
		move $t2, $v0

		li $t3, 16
		div $t2, $t2, $t3
		sub $t0, $t1, $t2

		la $a0, labela
		li $v0, 4
		syscall

		move $a0, $t0
		li $v0, 1
		syscall

		li $v0, 10
		syscall