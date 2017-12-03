.data
	var1: .byte 16
	var2: .byte 31
	var3: .space 1
	labela: .asciiz "Valoare expresiei var3 = 8 * var1 - [var2 / 16] este: "
.text
	main:
		lb $t1, var1
		lb $t2, var2

		li $t0, 8
		mulo $t1, $t1, $t0
		li $t0, 16
		div $t2, $t2, $t0
		sub $t3, $t1, $t2
		sb $t3, var3

		la $a0, labela
		li $v0, 4
		syscall
		lb $a0, var3
		li $v0, 1
		syscall

		li $v0, 10
		syscall
