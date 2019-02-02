.data
	labelx: .asciiz "Introduceti x: "
	labely: .asciiz "Introduceti y: "
	labela: .asciiz "Rezultatul ecuatiei[x / y] * {y / x} este: "
.text
	main:
		la $a0, labelx
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t1, $v0

		la $a0, labely
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t2, $v0

		div $t3, $t1, $t2
		rem $t4, $t2, $t1
		mulo $t0, $t3, $t4

		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t0
		li $v0, 1
		syscall

		li $v0, 10
		syscall