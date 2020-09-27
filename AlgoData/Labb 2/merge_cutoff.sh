#!/bin/bash
#
#This
gcc -o merge MergeSortCutoff.c

rm cutoffRes
rm iterate
#echo "--- Merge Sort ---"
for i in {0..50}; do
    echo $(($i)) >> iterate
    ./merge 10000 100 $(($i)) >> cutoffRes;
done