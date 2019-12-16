#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "dlmall.h"


#define ROUNDS 1
#define LOOPS 1000

int main(int argc, char const *argv[]){
    clock_t start,end;
    double time_used;
    double average;
    void *memlist[1000];

    for(int j = 0; j < ROUNDS; j++){
        start = clock();
        for(int i = 0; i < LOOPS; i++){

            size_t size = (size_t)16;    
            int *memory;
            memory = malloc(size);
            if(memory == NULL){
                fprintf(stderr, "malloc allocation failed\n");
                sanity();
                return(1);
            }
            *memory = 123;
            memlist[i] = memory;
        } 
        end = clock();
        time_used = ((double)(end - start)/CLOCKS_PER_SEC);
        average = average + time_used;
    }
    average = average / ROUNDS;
    printf("Average time used: %f",average);
    return 0;
}
