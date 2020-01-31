	addi $a0,$0,4	#A0 = N
	add $v0,$0,$a0	#V0 = A0
	beq $a0,$0,done	#Om a0 = 0 är vi klara

loop:
	addi $a0,$a0,-1	#a0 = a0-1
	beq $a0,$0,done	#Om a0 = 0 är vi klara
	mul $v0,$v0,$a0	#v0 = v0 * a0
	beq $0,$0,loop	#loop again
	
done:
	add $0,$0,$0	#Done
