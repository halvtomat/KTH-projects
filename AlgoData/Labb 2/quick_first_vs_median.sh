#!/bin/bash
#
#This
gcc -o first QuickSortFirst.c 
gcc -o median QuickSortMedian.c

rm frsRes
rm medRes
rm iterate
#echo "--- Quick Sort first ---"
for i in {1..50}; do
    echo $((100*$i)) >> iterate
    ./first $((1000*$i)) 100 >> frsRes;
done
#echo "--- Quick Sort median ---"
for i in {1..50}; do
    ./median $((1000*$i)) 100 >> medRes;
done