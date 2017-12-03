.data
	labela: .asciiz "Valoare din registrul $t1 este: "
.text
	main:
		ori $t1, $zero, 0x25
		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t1
		li $v0, 1
		syscall
		li $v0, 10
		syscall
