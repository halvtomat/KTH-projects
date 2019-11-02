#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[] ){
    int nrElements, *dynVec, i;
    FILE *fp = fopen("/Users/Daniel/Documents/AlgoData/PrepLab/Assignment3/3input.txt","r");

    fscanf(fp,"%d", &nrElements);
    const int size = nrElements;
    dynVec = (int *) malloc(size*sizeof(int));

    for(i = 0; i < size; i++){
        fscanf(fp,"%d", &nrElements);
        dynVec[i] = nrElements;
    }

    for(i = 0; i < size; i++){
    printf("%d",dynVec[size-(i+1)]);
    printf("\n");
    }

    system("pause");
    return 0;
}