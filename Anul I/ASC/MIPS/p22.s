.data
	label1: .asciiz "Introduceti numarul de caractere: "
	label2: .asciiz "Introduceti sirul: "
	labela: .asciiz "\nSirul de caractere oglindit este: "
	label3: .asciiz "Este oglindit"
	label4: .asciiz "nu este"
	sir: .align 0
		 .space 100
	cuvant: .align 0
			.space 100
.text
	main:
		la $a0, label1
		li $v0, 4
		syscall

		li $v0, 5
		syscall

		move $t0, $v0
		la $a0, label2
		li $v0, 4
		syscall

		la $a0, sir
		li $v0, 8
		move $a1, $t0
		add $a1, 1
		syscall

		li $t1, 0
		la $t2, sir
		jal push

		li $t1, 0
		la $t2, cuvant
		jal pop

		li $t3, 0
		la $t1, sir
		la $t2, cuvant
		jal check

		la $a0, labela
		li $v0, 4
		syscall

		la $a0, label3
		li $v0, 4
		syscall

		li $v0, 10
		syscall

	push:
		sub $sp, 4
		lb $t3, ($t2)
		sb $t3, ($sp)
		add $t1, 1
		add $t2, 1
		bne $t1, $t0, push
		jr $ra

	pop:
		lb $t3, ($sp)
		add $sp, 4
		sb $t3, ($t2)
		add $t2, 1
		add $t1, 1
		bne $t1, $t0, pop
		jr $ra

	check:
		lb $t4, ($t1)
		lb $t5, ($t2)
		add $t1, 1
		add $t2, 1
		add $t3, 1
		bne $t4, $t5, exit
		bne $t3, $t0, check
		jr $ra

	exit:
		la $a0, labela
		li $v0, 4
		syscall
		la $a0, label4
		li $v0, 4
		syscall
		li $v0, 10
		syscall

