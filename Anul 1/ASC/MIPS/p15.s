.data
	labela: .asciiz "Valoarea din registrul $t0 este: "
.text
	main:
		li $t0, 0
		li $t6, 7
		beq $t1, $t6, exista
		beq $t2, $t6, exista
		beq $t3, $t6, exista
		beq $t4, $t6, exista
		beq $t5, $t6, exista
		b exit

	exista:
		li $t0, 1

	exit:
		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t0
		li $v0, 1
		syscall

		li $v0, 10
		syscall