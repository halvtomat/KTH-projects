#!/bin/bash
#Argument 1 = shortest length of word to be accepted from the text
#Argument 2 = how many N * 100 words to read from the text

echo "COMPILING..."
gcc -o af alphaFilter.c
javac FrequencyCounterBST.java
javac FrequencyCounterOAST.java
clear

echo "-----ARGUMENTS--------------------------"
echo ""
echo "Smallest word length = " $1
echo "Number of words read = " $(($2*100))
echo ""
echo "-----BINARY SEARCH TREE TIME------------"
echo ""
./af < 98-0.txt | java FrequencyCounterBST $1 $2
echo ""
echo "-----ORDERED ARRAY SEARCH TREE TIME-----"
echo ""
./af < 98-0.txt | java FrequencyCounterOAST $1 $2
echo ""

#| WRDS  |  BST  | OAST  |
#|100    |6ms    |6ms    |
#|200    |10ms   |9ms    |  
#|400    |16ms   |13ms   |
#|800    |17ms   |18ms   |
#|1600   |22ms   |29ms   |
#|3200   |34ms   |31ms   |
#|6400   |38ms   |54ms   |
#|12800  |56ms   |83ms   |
#|25600  |91ms   |125ms  |
#|51200  |135ms  |243ms  |
#|102400 |177ms  |385ms  |
#|204800 |224ms  |779ms  |
#|409600 |221ms  |740ms  |
#|819200 |236ms  |747ms  |
