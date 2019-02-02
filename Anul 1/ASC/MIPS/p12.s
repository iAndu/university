.data
	x: .word 10
	y: .word 11
	z: .word 12
.text
	main:
		la $t1, x
		lw $t1, 4($t1)
		li $t1, 14
		la $t2, x
		sh $t1, 8($t2)

		li $v0, 10
		syscall