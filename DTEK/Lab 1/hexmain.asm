  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,10		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
hexasc:
	
	andi $a0,$a0,0xf	# removes all bits but the 4 least significant
	
	li $t0,10		
	
	ble $t0,$a0, boks	# if (a0 <= t0) execute boks
	
	addi $v0,$a0,0x30	# convert the number at a0 to the ASCII code for the character and put in v0
	
	jr $ra			# return
	
boks: 
	addi $v0,$a0,0x37	# convert the number at a0 to the ASCII code for the character and put in v0
	
	jr $ra			# return
  #

