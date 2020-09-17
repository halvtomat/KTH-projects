#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/*  Swap two elements in an array*/
void Swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int Partition(int a[],int b, int c){
    int d = *(a+b);
    int i = b-1;
    int j;
    for(j = b; j <= c - 1; j++){
        if(*(a+j) < d){
            i++;
            Swap(a+i,a+j);
        }
    }
    Swap(a+i+1,a+c);
    return i+1;
}
void QuickSort(int a[], int b, int c){
    if(b < c){
        int d = Partition(a,b,c);
        QuickSort(a,b,d-1);
        QuickSort(a,d+1,c);
    }
}
int main(int argc, char const *argv[])
{
    clock_t s,e;
    double timeUsed;
    const int SIZE = atoi((char *)argv[1]);
    const int ITERATIONS = atoi((char *)argv[2]);
    int k;
    for(k = 0; k < ITERATIONS; k++){
        srand(time(NULL));
        int a[SIZE];
        int i;
        for(i = 0; i < SIZE; i++){
            a[i] = (rand() % SIZE);
            //printf("%d",a[i]);
            //printf("%c",',');
        }
        s = clock();
        QuickSort(a,0, SIZE-1);
        e = clock();
        timeUsed += ((double) (e - s)) /CLOCKS_PER_SEC;
        /*printf("%c",'\n');
        for(i = 0; i < SIZE; i++){
            printf("%d",a[i]);
            printf("%c",',');
        }*/
    }
    printf("%f%s",timeUsed/100, "\n");
    return 0;
}
/*  RESULTS: question 9
    SIZE = 500000; Iterations = 100; Insertion cutoff = 30; TIME = 7.818
    SIZE = 500000; Iterations = 100; Insertion cutoff = 20; TIME = 7.836
    SIZE = 500000; Iterations = 100; Insertion cutoff = 10; TIME = 8.434
    SIZE = 500000; Iterations = 100; Insertion cutoff = 5;  TIME = 8.753
    SIZE = 500000; Iterations = 100; Insertion cutoff = 0;  TIME = 8.978
    */
/*  RESULTS: question 8
    SIZE = 1000;   Iterations = 100; Insertion cutoff = 0; TIME = 0.001
    SIZE = 10000;  Iterations = 100; Insertion cutoff = 0; TIME = 0.139
    SIZE = 100000; Iterations = 100; Insertion cutoff = 0; TIME = 1.652
    SIZE = 200000; Iterations = 100; Insertion cutoff = 0; TIME = 3.427
    */