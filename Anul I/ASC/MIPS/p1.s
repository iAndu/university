.data
.text
	main:
		add $t1, $t1, $t2
		sub $t4, $t1, $t3
		li $v0, 10
		syscall