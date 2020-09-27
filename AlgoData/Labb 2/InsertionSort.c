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
void insertionSort(int a[], int n){
    int i,j,k;
    for(i = 1; i < n; i++){
        k = a[i];
        j = i - 1;
        while(j >= 0 && a[j] > k){
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = k;
        //print(a,n);
    }
}

int main(int argc, char const *argv[]){
    // int n; 
    // scanf("%d", &n);
    // int a[n];
    // for(int i = 0; i < n; i++){
    //     scanf("%d", &a[i]);
    // }
    // insertionSort(a,n);



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
        insertionSort(a,SIZE);
        e = clock();
        timeUsed += ((double) (e - s)) /CLOCKS_PER_SEC;
        /*printf("%c",'\n');
        for(i = 0; i < SIZE; i++){
            printf("%d",a[i]);
            printf("%c",',');
        }*/
    }
    printf("%f%s",timeUsed, "\n");
    return 0;
}