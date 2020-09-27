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
    echo $((10*$i)) >> iterate
    ./insertion $((10*$i)) 10 >> insRes;
done
#echo "--- Merge Sort ---"
for i in {1..20}; do
    ./merge $((10*$i)) 10 0 >> merRes;
done