#include <stdio.h>
int main(int argc, const char* argv[] ){
    char charArray[100];
    int i = 0;
    char c;
    for(i;i < 100; i++){
        c = getc(stdin);
        if(c == '\n') break;
        charArray[i] = c;
    }
    for(i;i >= 0; i--) putc(*(charArray+i),stdout);
    return 0;
}