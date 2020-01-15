#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>
#include "dlmall_2.0.h"
#include "dlmall.h"
#include "rand.h"

#define ROUNDS 100
#define LOOP 100000
#define BUFFER 50

int main(int argc, char const *argv[]){
    mallopt(M_TOP_PAD,64*1024);
    void *init = sbrk(0);
    void *current;
    void *buffer[BUFFER];
    for(int i = 0; i < BUFFER; i++){
        buffer[i] = NULL;
    }
    clock_t start,end;
    double time_used;
    double average[3];
    double difference;

    //printf("The initial top of the heap is %p.\n", init);
//------------------------------------- DALLOC_IMPROVED TEST ---------------------------------
    for(int i = 0; i < ROUNDS; i++){
        start = clock();
        for(int j = 0; j < LOOP; j++){
            int index = rand() % BUFFER;
            if(buffer[index] != NULL){
                dfree2(buffer[index]);
            }
            size_t size = 256;        
            int *memory;
            memory = dalloc2(size);

            if(memory == NULL){
                fprintf(stderr, "dalloc allocation failed\n");
                sanity2();
                return(1);
            }
            buffer[index] = memory;
            *memory = 123;
            //sanity2();
        }
        
        current = sbrk(0);
        int allocated = (int)((current - init) / 1024);
        
        //printf("%d\n", i);
        //printf("The current top of the heap is %p.\n", current);
        //printf("    increased by %d Kbyte\n", allocated);
        
        end = clock();
        time_used = ((double)(end - start)/CLOCKS_PER_SEC);
        average[0] = average[0] + time_used;
        //sanity2();
    }
    average[0] = average[0] / ROUNDS;
    difference = (average[0] / average[0])*100;
    printf("Dalloc_improved average time used:  %f  diff:   %.1f%%\n",average[0],difference);

    for(int i = 0; i < BUFFER; i++){
        buffer[i] = NULL;
    }
    //--------------------------------------- DALLOC TEST -----------------------------
    for(int i = 0; i < ROUNDS; i++){
        start = clock();
        for(int j = 0; j < LOOP; j++){
            int index = rand() % BUFFER;
            if(buffer[index] != NULL){
                dfree(buffer[index]);
            }
            size_t size = (size_t)request();        
            int *memory;
            memory = dalloc(size);
            buffer[index] = memory;
            *memory = 123;
        }
        end = clock();
        time_used = ((double)(end - start)/CLOCKS_PER_SEC);
        average[1] = average[1] + time_used;
    }
    average[1] = average[1] / ROUNDS;
    difference = (average[1] / average[0])*100;
    printf("Dalloc average time used:           %f  diff:   %.1f%%\n",average[1],difference);

    for(int i = 0; i < BUFFER; i++){
        buffer[i] = NULL;
    }
    //--------------------------------------- MALLOC TEST ---------------------------------
    for(int i = 0; i < ROUNDS; i++){
        start = clock();
        for(int j = 0; j < LOOP; j++){
            int index = rand() % BUFFER;
            if(buffer[index] != NULL){
                free(buffer[index]);
            }
            size_t size = (size_t)request();        
            int *memory;
            memory = malloc(size);
            buffer[index] = memory;
            *memory = 123;
        }
        end = clock();
        time_used = ((double)(end - start)/CLOCKS_PER_SEC);
        average[2] = average[2] + time_used;
    }
    average[2] = average[2] / ROUNDS;
    difference = (average[2] / average[0])*100;
    printf("Malloc average time used:           %f  diff:   %.1f%%\n",average[2],difference);
    return 0;
}
