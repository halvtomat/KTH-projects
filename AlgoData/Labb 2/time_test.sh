#!/bin/bash
#
#This
gcc -o insertion InsertionSort.c 
gcc -o merge MergeSort.c

rm insRes
rm merRes
#echo "--- Insertion Sort ---"
for i in {1..4}; do
    ./insertion $((10**$i)) 10 >> insRes;
done
#echo "--- Merge Sort ---"
for i in {1..5}; do
    ./merge $((10**$i)) 10 >> merRes;
done