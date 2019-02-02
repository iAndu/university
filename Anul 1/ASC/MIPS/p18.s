.data
	vector: .align 2
			.space 50
	label1: .asciiz "Introduceti numarul de componente: "
	label2: .asciiz "Introduceti componenta "
	labels: .asciiz ": "
	labela: .asciiz "Suma componentelor pozitive este: "
.text
	main:
		# Afisare label
		la $a0, label1
		li $v0, 4
		syscall
		# Citire nr comp
		li $v0, 5
		syscall
		# Retinerenr comp in $t0
		move $t0, $v0
		# $t1 - contor
		li $t1, 0
		la $t2, vector
		jal citeste

		la $t2, vector
		li $t1, 0
		li $t3, 0
		jal suma

		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t3
		li $v0, 1
		syscall

		li $v0, 10
		syscall

	citeste:
		# Afisare label
		add $t1, 1
		la $a0, label2
		li $v0, 4
		syscall
		move $a0, $t1
		li $v0, 1
		syscall
		la $a0, labels
		li $v0, 4
		syscall
		# Citire numar
		li $v0, 5
		syscall
		# Salvare in vector
		sw $v0, ($t2)
		add $t2, 4
		# if ($t0 != $t1) nr comp totale != nr comp citite
		bne $t0, $t1, citeste
		# Revenire in main dupa ce termin de citit
		jr $ra

	aduna:
		add $t3, $t3, $t4
		beq $t1, $t0, revenire

	suma:
		lw $t4, ($t2)
		add $t2, 4
		add $t1, 1
		bgtz $t4, aduna
		bne $t1, $t0, suma
		jr $ra

	revenire:
		jr $ra