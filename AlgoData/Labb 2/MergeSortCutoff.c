#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void print(int a[], int n){
    printf("%c",'[');
    for(int i = 0; i < n; i++){
        printf("%d", a[i]);
        if(i < n - 1) printf("%c", ',');
    }
    printf("%s","]\n");
}

void insertionSort(int a[], int b, int c){
    int i,j,k;
    for(i = b+1; i < c; i++){
        k = a[i];
        j = i - 1;
        while(j >= b && a[j] > k){
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = k;
    }
}

void Merge(int a[], int b, int c, int d){
    //print(a,5);
    //printf("%d%c%d%c%d%c",b,',',c,',',d,'\n');

    int n1 = c-b+1;
    int n2 = d - c;

    int t1[n1],t2[n2];

    for(int i = 0; i < n1; i++)t1[i] = *(a+b+i);
    for(int i = 0; i < n2; i++)t2[i] = *(a+c+i+1);

    int i = 0, j = 0, k = b;
    while(i < n1 && j < n2){
        if(t1[i] <= t2[j])*(a+k) = t1[i++];
        else *(a+k) = t2[j++];
        k++;
    }
    while(i < n1) *(a+k++) = t1[i++];
    while(j < n2) *(a+k++) = t2[j++];
}
void MergeSort(int a[], int b, int c, int CUTOFF){
    //printf("%d%s%d%s",b, " , ", c, "\n");
    if(b < c){
        if(c - b <= CUTOFF){
            //printf("%d%s%d%s",CUTOFF, " , ", b-c, " : ");
            //printf("%s","cutoff\n");
            insertionSort(a,b,c);
        }
        else{
            int d = (b+c)/2;
            MergeSort(a,b,d, CUTOFF);
            MergeSort(a,d+1,c, CUTOFF);
            Merge(a,b,d,c);
        }
    }
}
int main(int argc, char const *argv[]){
    // int n; 
    // scanf("%d", &n);
    // int a[n];
    // for(int i = 0; i < n; i++){
    //     scanf("%d", &a[i]);
    // }
    // print(a,n);
    // MergeSort(a,0, n-1);
    // print(a,n);
    clock_t s,e;
    double timeUsed;
    const int SIZE = atoi((char *)argv[1]);
    const int ITERATIONS = atoi((char *)argv[2]);
    const int CUTOFF = atoi((char *)argv[3]);
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
        MergeSort(a,0, SIZE-1, CUTOFF);
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
/*  RESULTS: question 8
    SIZE = 1000;   Iterations = 100; TIME = 0.005
    SIZE = 10000;  Iterations = 100; TIME = 0.072
    SIZE = 100000; Iterations = 100; TIME = 0.831
    SIZE = 200000; Iterations = 100; TIME = 1.729
*/
