  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,0
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
hexasc:
	
	andi $a0,$a0,0xf	# removes all bits but the 4 least significant
	li $t0,10		
	
	ble $t0,$a0, boks	# if (a0 <= t0) execute boks
	nop
	
	addi $v0,$a0,0x30	# convert the number at a0 to the ASCII code for the character and put in v0
	jr $ra			# return
	nop
	
boks: 
	addi $v0,$a0,0x37	# convert the number at a0 to the ASCII code for the character and put in v0
	
	jr $ra			# return
	nop
  #
	
time2string:
  	PUSH $ra   	    # push the address at ra to free up ra
 	PUSH $s0   	    # push the address at s0 to free up s0
 	PUSH $s1	    # push the address at s1 to free up s1
  
 	move $s1,$a0	    # save a0 for later use in s1
	move $s0,$a1	    # save a1 for later use in s0
  
  	andi $a0,$s0,0xf000 # mask a1 to get the first digit
  	srl $a0,$a0,12      # shift into position
  	jal hexasc          # call hexasc
  	nop
  	sb $v0,+0($s1)      # store first digit in first byte
  
  	andi $a0,$s0,0xf00  # mask a1 to get the second digit
  	srl $a0,$a0,8       # shift into position
  	jal hexasc          # call hexasc
  	nop
  	sb $v0,+1($s1)      # store second digit in second byte
  
  	li $t0,0x3a         # load ASCII code of colon
  	sb $t0,+2($s1)      # store colon in third byte
  
  	andi $a0,$s0,0xf0   # mask a1 to get the third digit
  	srl $a0,$a0,4       # shift into position
  	jal hexasc          # call hexasc
  	nop
  	sb $v0,+3($s1)      # store third digit in fourth byte
  
  	andi $a0,$s0,0xf    # mask a1 to get the fourth digit
  	jal hexasc	    # call hexasc
  	nop
  	sb $v0,+4($s1)      # store fourth digit in fifth byte
  
  	li $t0,0x00	    # load null-byte
  	sb $t0,+5($s1)      # store null-byte in sixth byte
  
  	POP $s1	      	    # pop the old values of s1, s0 and ra back
  	POP $s0		    # pop
  	POP $ra		    # pop
  
  	jr $ra     	    # return
  	nop
	
delay:			# orkar inte kommentera men den är bra
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
