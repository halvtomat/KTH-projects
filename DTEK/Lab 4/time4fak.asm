	addi $a0,$0,4	#A0 = N
	add $v0,$0,$a0	#V0 = A0
	beq $a0,$0,done	#Om a0 = 0 är vi klara

loop:
	addi $a1,$a0,-1	#a1 = a0-1
	addi $a0,$a0,-1	#a0 = a0-1
	beq $a0,$0,done	#Om a0 = 0 är vi klara
	add $a2,$0,$v0	#a2 = v0
loop2:
	addi $a1,$a1,-1	#a1 = a1-1
	beq $a1,$0,loop	#Om a1 = 0, gå tillbaka till loop
	add $v0,$v0,$a2	#v0 = v0 + a2
	beq $0,$0,loop2	#Gå till loop2
done:
	add $0,$0,$0	#Done
