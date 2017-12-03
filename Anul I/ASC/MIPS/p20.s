.data
	vector: .align 2
			.space 80
	labeln: .asciiz "Introduceti numarul de componente: "
	labeli: .asciiz "Introduceti componenta "
	labels: .asciiz ": "
	labela: .asciiz "Componentele vectorului sunt: "
	labelsp: .asciiz " "
.text
	main:
		li $v0, 4
		la $a0, labeln
		syscall
		li $v0, 5
		syscall
		# $t0 - numarul de componente
		move $t0, $v0
		# $t1 - contor
		li $t1, 0
		# $t2 - adresa curenta in vector
		la $t2, vector
		b citeste

	citeste:
		add $t1, 1
		li $v0, 4
		la $a0, labeli
		syscall
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 4
		la $a0, labels
		syscall
		li $v0, 5
		syscall
		sw $v0, ($t2)
		add $t2, 4
		bne $t1, $t0, citeste
		li $t1, 0
		la $t2, vector
		li $v0, 4
		la $a0, labela
		syscall
		b scrie

	scrie:
		lw $t3, ($t2)
		add $t2, 4
		add $t1, 1
		li $v0, 1
		move $a0, $t3
		syscall
		li $v0, 4
		la $a0,labelsp
		syscall
		bne $t1, $t0, scrie
		b exit

	exit:
		li $v0, 10
		syscall
