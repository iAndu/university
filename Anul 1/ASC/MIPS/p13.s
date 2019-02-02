.data
	labela: .asciiz "La adresa lui x + 4 se afla valoarea: "
	x: .word 5
.text
	main:
		lw $t0, x

		li $t1, 2
		mulo $t1, $t1, $t0
		mulo $t1, $t1, $t0 #2x^2

		li $t2, 4
		mulo $t2, $t2, $t0

		sub $t1, $t1, $t2
		add $t1, 12

		la $t0, x
		sw $t1, 4($t0)

		lw $t0, 4($t0)
		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t0
		li $v0, 1
		syscall

		li $v0, 10
		syscall
