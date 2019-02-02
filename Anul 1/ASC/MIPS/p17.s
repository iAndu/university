.data
	cuvant: .align 0
			.space 50
	label1: .asciiz "Introduceti string-ul: "
	label2: .asciiz "Numarul de caractere al sirului este: "
.text
	main:
		la $a0, label1
		li $v0, 4
		syscall
		la $a0, cuvant
		li $a1, 50
		li $v0, 8
		syscall

		li $t0, 0
		la $t1, cuvant
		li $t3, 10
		b numara_caractere

	numara_caractere:
		lb $t2, ($t1)
		beq $t2, $t3, exit
		add $t0, 1
		add $t1, 1
		b numara_caractere

	exit:
		la $a0, label2
		li $v0, 4
		syscall
		move $a0, $t0
		li $v0, 1
		syscall

		li $v0, 10
		syscall