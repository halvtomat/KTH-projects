#include "dlmall.h"
#include <stdio.h>

int main(int argc, char const *argv[]){
    size_t n = 0;
    for(n; n <= 64; n = n + 4){
        printf("testing dalloc with size_t = %ld\n",n);
        void* test = dalloc(n);
        printf("    data at: %p\n\n",test);
        dfree(test);
    }

    sanity();
    
    return 0;
}
