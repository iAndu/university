.data
	meniu: .asciiz "1. Suma elementelor;\n2. Ultimul element;\n3. Elementele mai mari decat n;\n4. Iesire din program\n"
	optiune: .asciiz "Introduceti optiunea: "
	lungime: .asciiz "Introduceti numarul de componente: "
	componenta: .asciiz "Introduceti componenta "
	suma_elemente: .asciiz "Suma elementelor este: "
	ultimul_element: .asciiz "Ultimul element al vectorului este: "
	greater_elements: .asciiz "Elementele mai mari decat "
	sunt: .asciiz " sunt: "
	enter: .asciiz "\n"
	spatiu: .asciiz ": "
	spatiuu: .asciiz " "
	vector: .align 2
			.space 80
.text
	main:
		jal citeste_lungime
		b ciclu

	ciclu:
		jal afiseaza_meniu
		jal alege_optiunea
		li $t4, 1
		li $t1, 0
		la $t2, vector
		li $t5, 0
		beq $t4, $t3, suma
		add $t4, 1
		beq $t4, $t3, ultim
		add $t4, 1
		beq $t4, $t3, afiseaza_greater
		b exit

	citeste_lungime:
		li $v0, 4
		la $a0, lungime
		syscall
		li $v0, 5
		syscall
		move $t0, $v0
		li $t1, 0
		la $t2, vector
		b citeste_componente

	citeste_componente:
		add $t1, 1
		li $v0, 4
		la $a0, componenta
		syscall
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 4
		la $a0, spatiu
		syscall
		li $v0, 5
		syscall
		sw $v0, ($t2)
		add $t2, 4
		bne $t1, $t0, citeste_componente
		jr $ra

	afiseaza_meniu:
		li $v0, 4
		la $a0, meniu
		syscall
		jr $ra

	alege_optiunea:
		li $v0, 4
		la $a0, optiune
		syscall
		li $v0, 5
		syscall
		move $t3, $v0
		jr $ra

	suma:
		add $t1, 1
		lw $t6, ($t2)
		add $t2, 4
		add $t5, $t5, $t6
		bne $t1, $t0, suma
		li $v0, 4
		la $a0, suma_elemente
		syscall
		li $v0, 1
		move $a0, $t5
		syscall
		li $v0, 4
		la $a0, enter
		syscall
		b ciclu

	ultim:
		li $t5, 4
		mulo $t5, $t5, $t0
		sub $t5, 4
		add $t2, $t2, $t5
		li $v0, 4
		la $a0, ultimul_element
		syscall
		lw $a0, ($t2)
		li $v0, 1
		syscall
		li $v0, 4
		la $a0, enter
		syscall
		b ciclu

	afiseaza_greater:
		li $v0, 4
		la $a0, greater_elements
		syscall
		li $v0, 1
		move $a0, $t0
		syscall
		li $v0, 4
		la $a0, sunt
		syscall
		li $v0, 4
		la $a0, enter
		syscall
		b greater

	greater:
		add $t1, 1
		lw $t5, ($t2)
		add $t2, 4
		jal salveaza_adresa
		bgt $t5, $t0, afiseaza
		bne $t1, $t0, greater
		b ciclu

	afiseaza:
		li $v0, 1
		move $a0, $t5
		syscall
		li $v0, 4
		la $a0, spatiuu
		syscall
		jr $t7

	salveaza_adresa:
		move $t7, $ra
		add $t7, 8
		jr $ra

	exit:
		li $v0, 10
		syscall
