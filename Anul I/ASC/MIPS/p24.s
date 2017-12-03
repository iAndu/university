.data 
    input1: .asciiz "Introduceti sirul: "
    input2: .asciiz "Introduceti numarul de caractere: "
    sir: .align 0
        .space 100

.text 
    main:
 la $a0, input2
 li $v0, 4
 syscall

 li $v0, 5
 syscall
 move $t1, $v0

 la $a0, input1
 li $v0, 4
 syscall
 
 li $v0, 8
 la $a0, sir
 addi $a1, $t1, 1
 syscall

 la $a0, sir
 li $t2, 1
 jal solution
 
 li $v0, 1
 move $a0, $t0
 syscall
 
 li $v0, 10
 syscall

 solution:
  lb $t3, ($a0)
  move $a1, $a0
  li $t5, 1
  bne $t2, $t1, chestie
  jr $ra

 chestie:
  addi $t2, $t2, 1
  addi $a1, $a1, 1
  lb $t4, ($a1)
  beq $t3, $t4, next
  move $a0, $a1
  bgt $t5, $t0, save 
  b solution

 next:
  addi $t5, $t5, 1
  b chestie

 save:
  move $t0, $t5
  b solution