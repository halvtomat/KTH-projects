#include <stdio.h>
void recur(char c){
    if(c == '\n') return;
    char d = getc(stdin);
    recur(d);
    putc(c,stdout);
}
int main(int argc, const char* argv[] ){
    char c = getc(stdin);
    recur(c);
    return 0;
}