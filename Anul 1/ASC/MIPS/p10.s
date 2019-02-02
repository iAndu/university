.data
	labela: .asciiz "Valorile din registrul $t1, respectiv $t2 sunt: "
	spatiu: .byte ' '
.text
	main:
		li $t1, 1
		li $t2, 2
		move $t3, $t1
		move $t1, $t2
		move $t2, $t3
		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t1
		li $v0, 1
		syscall
		la $a0, spatiu
		li $v0, 4
		syscall
		move $a0, $t2
		li $v0, 1
		syscall
		li $v0, 10
		syscall
