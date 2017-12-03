.data
	labela: .asciiz "Valoare din registrul $t1 este: "
.text
	main:
		li $t0, 0x12345678
		li $t2, 0xc091a2b3
		li $t4, 0
		li $t5, 32
		li $t3, 1
		
		jal rotate
		move $t6, $t1

		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t0
		li $v0, 1
		syscall

		li $v0, 10
		syscall

	rotate:
		beq $t4, $t5, save_left
		rol $t0, $t0, $t3
		add $t4, 1
		bne $t0, $t2, rotate
		jr $ra

	save_left:
		move $t1, $t0
		li $t4, 0
		b shift_left

	shift_left:
		beq $t4, $t5, save_right
		sll $t1, $t1, $t3
		add $t4, 1
		bne $t1, $t2, shift_left
		jr $ra

	save_right:
		move $t1, $t0
		b shift_right

	shift_right:
		srl $t1, $t1, $t3
		bne $t1, $t2, shift_right
		jr $ra
