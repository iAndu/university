.data
	labela: .asciiz "Valoarea din registrul $t2 este: "
.text
	main:
		sge $t2, $t1, $zero

		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t2
		li $v0, 1
		syscall

		li $v0, 10
		syscall