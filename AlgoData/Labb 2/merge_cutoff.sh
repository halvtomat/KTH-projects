#!/bin/bash
#
#This
gcc -o merge MergeSortCutoff.c

rm cutoffRes
rm iterate
#echo "--- Merge Sort ---"
for i in {50..100}; do
    echo $(($i)) >> iterate
    ./merge 10000 1000 $(($i)) >> cutoffRes;
done