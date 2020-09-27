#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int swapcount = 0;

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
            swapcount++;
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = k;
        print(a,n);
    }
}

int main(int argc, char const *argv[]){
    int n; 
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    insertionSort(a,n);
    printf("%s%d%c", "Swap count = ", swapcount, '\n');
    
    return 0;
}