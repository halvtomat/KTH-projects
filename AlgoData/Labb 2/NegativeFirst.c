#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/*  Returns the number of ints in an array that are negative (n < 0)
    nc == amount of elements in a[0...i]  < 0
    nc =< i*/
int CountNegatives(int a[], int size){
    int nc = 0;
    int i;
    for(i = 0; i < size; i++){
        if(*(a+i) < 0) nc++;
    }
    return nc;
}
/*  Swap two elements in an array*/
void Swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
/*  NegativeFirst function rearranges an array for all negatives in the array to be put at the start of the array
    if an element in a[0...nc] > 0 is found, there must exist an element a[nc...SIZE] < 0
    the loop searches for these elements and swap them
    after each swap there must exist one less negative element in a[nc...SIZE] so therefore offset nc by + 1 for every swap or nc+o , o++
    Calculated and validated time complexity = O(N*N)
*/
void NegativeFirst(int a[], int size){
    int i;
    int o = 0;
    int nc = CountNegatives(a, size);
    for(i = 0; i < nc; i++){
        if(*(a+i) >= 0){
            int j = nc+o++;
            while(*(a+j) > 0) j++;
            Swap(a+i,a+j);
        }
    }
}

/*  Main method tests the program by generating an array with size SIZE with randomized elements ranging from -50 to 50 and 
    than starting a timer to see how long it takes to put all the negatives in the array at the start*/
int main(int argc, char const *argv[]){
    clock_t s,e;
    double timeUsed;
    const int SIZE = 400000;
    srand(time(NULL));
    int a[SIZE];
    int i;
    for(i = 0; i < SIZE; i++){
        a[i] = (rand() % 100) - 50;
        /*printf("%d",a[i]);
        printf("%c",',');*/
    }
    s = clock();
    NegativeFirst(a, SIZE);
    e = clock();
    timeUsed = ((double) (e - s)) /CLOCKS_PER_SEC;
    printf("%c",'\n');
    /*for(i = 0; i < SIZE; i++){
        printf("%d",a[i]);
        printf("%c",',');
    }*/
    printf("%s","Time taken: ");
    printf("%f%c",timeUsed, '\n');
    return 0;
}
