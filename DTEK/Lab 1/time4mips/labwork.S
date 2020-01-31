  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  .global delay
  .global time2string
  .data
  .text
  # Please add your own code below this line
delay:
  sub $t0,$a0,1
  li $a0,0
  li $a1,4711
  move $t1,$ra
  
  bgezal $t0,loop
  nop
  
  move $ra,$t1
  move $a0,$t0
  
  bgtz $t0,delay
  nop
  
  jr $ra
  nop
loop:
  addi $a0,$a0,1
  bne $a0,$a1,loop
  nop
  jr $ra
  nop

  hexasc:
  
  andi $a0,$a0,0xf  # removes all bits but the 4 least significant
  li $t0,10   
  
  ble $t0,$a0, boks # if (a0 <= t0) execute boks
  nop
  
  addi $v0,$a0,0x30 # convert the number at a0 to the ASCII code for the character and put in v0
  jr $ra      # return
  nop
  
boks: 
  addi $v0,$a0,0x37 # convert the number at a0 to the ASCII code for the character and put in v0
  
  jr $ra      # return
  nop
  #
  
time2string:
  PUSH $ra    # save the address at ra in t1 to free up ra
  PUSH $s0
  PUSH $s1    # save the address at a0 in t2 to free up a0
  
  move $s1,$a0
  move $s0,$a1
  
  andi $a0,$s0,0xf000 # mask a1 to get the first digit
  srl $a0,$a0,12    # shift into position
  jal hexasc    # call hexasc
  nop
  sb $v0,+0($s1)    # store first digit in first byte
  
  andi $a0,$s0,0xf00  # mask a1 to get the second digit
  srl $a0,$a0,8   # shift into position
  jal hexasc    # call hexasc
  nop
  sb $v0,+1($s1)    # store second digit in second byte
  
  li $t0,0x3a   # load ASCII code of colon
  sb $t0,+2($s1)    # store colon in third byte
  
  andi $a0,$s0,0xf0 # mask a1 to get the third digit
  srl $a0,$a0,4   # shift into position
  jal hexasc    # call hexasc
  nop
  sb $v0,+3($s1)    # store third digit in fourth byte
  
  andi $a0,$s0,0xf  # mask a1 to get the fourth digit
  jal hexasc    # call hexasc
  nop
  sb $v0,+4($s1)    # store fourth digit in fifth byte
  
  li $t0,0x00   # load null-byte
  sb $t0,+5($s1)    # store null-byte in sixth byte
  
  POP $ra
  POP $s0
  POP $s1
  
  jr $ra      # return
  nop
  #

