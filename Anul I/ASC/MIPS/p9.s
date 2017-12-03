.data
	x: .word 23
	labela: .asciiz "Valoare lui x este: "
.text
	main:
		li $t0, 5
		sw $t0, x
		la $a0, labela
		li $v0, 4
		syscall
		lw $a0, x
		li $v0, 1
		syscall
		li $v0, 10
		syscall
