#include <stdlib.h>
#include <stdio.h>
#include "rand.h"

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("usage: rand <loop>\n");
        exit(1);
    }
    int loop = atoi(argv[1]);
    for(int i = 0; i < loop; i++){
        int size = request();
        printf("%d\n", size);
    }
}
