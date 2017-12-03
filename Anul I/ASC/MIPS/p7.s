.data
	labela: .asciiz "Valoare din registrul $t2 este: "
.text
	main:
		li $t0, 0x1234
		li $t1, 0x91a0
		li $t3, 1
		jal rotate
		move $t2, $t0
		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t2
		li $v0, 1
		syscall
		li $v0, 10
		syscall

	rotate:
		rol $t0, $t0, $t3
		bne $t0, $t1, rotate
		jr $ra
