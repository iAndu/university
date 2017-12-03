.data
 input1: .asciiz "Cate cifre are numarul?"
 input2: .asciiz "Introduceti numarul: "
 input3: .asciiz "Introduceti cifra: "

 output1: .asciiz "\nDa"
 output2: .asciiz "\nNu"

 numar: .align 0
  .space 100

 cifra: .align 0
  .space 1

.text
main:
 li $v0, 4
 la $a0, input1
 syscall

 li $v0, 5
 syscall

 move $t0, $v0
 
 la $a0, input2
 li $v0, 4
 syscall
 
 la $a0, numar
 addi $a1, $t0, 1
 li $v0, 8
 syscall

 la $a0, input3
 li $v0, 4
 syscall
 
 la $a0, cifra
 li $a1, 2
 li $v0, 8
 syscall
 
 li $t5, 0
 la $a0, numar
 jal check
 
 la $a0, output2
 li $v0, 4
 syscall
 
 li $v0, 10
 syscall

check: 
 lb $t1, ($a0)
 lb $t2, cifra
 beq $t1, $t2, exit
 addi $a0, $a0, 1
 addi $t5, $t5, 1
 bne $t0, $t5, check
 jr $ra

exit: 
 la $a0, output1
 li $v0, 4
 syscall
 li $v0, 10
 syscall