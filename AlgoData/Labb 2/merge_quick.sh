#!/bin/bash
#
#This
gcc -o quick QuickSort.c 
gcc -o merge MergeSort.c

rm qckRes
rm merRes
rm iterate
#echo "--- Quick Sort ---"
for i in {1..50}; do
    echo $((100*$i)) >> iterate
    ./quick $((1000*$i)) 100 >> qckRes;
done
#echo "--- Merge Sort ---"
for i in {1..50}; do
    ./merge $((1000*$i)) 100 >> merRes;
done