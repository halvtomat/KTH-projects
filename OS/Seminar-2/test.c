#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dlmall.h"
#include "rand.h"


#define ROUNDS 10
#define LOOP 100000
#define BUFFER 100

int main(int argc, char const *argv[]){
    void *init = sbrk(0);
    void *current;
    void *buffer[BUFFER];
    for(int i = 0; i < BUFFER; i++){
        buffer[i] = NULL;
    }

    printf("The initial top of the heap is %p.\n", init);

    for(int i = 0; i < ROUNDS; i++){
        for(int j = 0; j < LOOP; j++){
            int index = rand() % BUFFER;
            if(buffer[index] != NULL){
                dfree(buffer[index]);
            }
            size_t size = (size_t)request();        
            int *memory;
            memory = dalloc(size);

            if(memory == NULL){
                fprintf(stderr, "malloc allocation failed\n");
                sanity();
                return(1);
            }
            buffer[index] = memory;
            *memory = 123;
        }
        
        current = sbrk(0);
        int allocated = (int)((current - init) / 1024);
        printf("%d\n", i);
        printf("The current top of the heap is %p.\n", current);
        printf("    increased by %d Kbyte\n", allocated);
    }
    return 0;
}
