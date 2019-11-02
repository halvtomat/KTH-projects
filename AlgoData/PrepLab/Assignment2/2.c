#include <stdio.h>

int main(int argc, const char* argv[] ){
    FILE *fp = fopen("/Users/Daniel/Documents/AlgoData/PrepLab/Assignment2/2input.txt", "r" );
    if(fp == NULL){
        printf("Error reading file");
        return 0;
    }

    int c;
    do{
        c = fgetc(fp);
        if(c == 'a'){
            printf("%c", 'x');
        } else{
            printf("%c",c);
        }
    } while (c != EOF);

    system("pause");
    return 0;
}