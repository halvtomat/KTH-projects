#!/bin/bash
#
#This
gcc -o insertion InsertionSort.c 
gcc -o merge MergeSort.c

rm insRes
rm merRes
rm iterate
#echo "--- Insertion Sort ---"
for i in {1..20}; do
    echo $((100*$i)) >> iterate
    ./insertion $((100*$i)) 100 >> insRes;
done
#echo "--- Merge Sort ---"
for i in {1..20}; do
    ./merge $((100*$i)) 100 0 >> merRes;
done