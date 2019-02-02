.data
	labelx: .asciiz "Introduceti x: "
	labely: .asciiz "Introduceti y: "
	labelz: .asciiz "Introduceti z: "
	labelw: .asciiz "Introduceti w: "
	labela: .asciiz "Rezultatul ecuatiei (x OR y) AND (NOT z) XOR w este: "
.text
	main:
		la $a0, labelx
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t1, $v0

		la $a0, labely
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t2, $v0

		la $a0, labelz
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t3, $v0

		la $a0, labelw
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $t4, $v0

		or $t1, $t1, $t2
		not $t3, $t3
		and $t1, $t1, $t3
		xor $t5, $t1, $t4

		la $a0, labela
		li $v0, 4
		syscall
		move $a0, $t5
		li $v0, 1
		syscall

		li $v0, 10
		syscall