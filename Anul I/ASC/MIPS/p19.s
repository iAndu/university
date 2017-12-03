.data
	il: .align 2
		.space 4
	labeli: .asciiz "Introduceti un numar: "
	labela: .asciiz "Valoarea variabilei il este: "
.text
	main:
		li $v0, 4
		la $a0, labeli
		syscall
		li $v0, 5
		syscall
		move $t0, $v0
		sw $t0, il
		lw $t1, il
		li $v0, 4
		la $a0, labela
		syscall
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 10
		syscall