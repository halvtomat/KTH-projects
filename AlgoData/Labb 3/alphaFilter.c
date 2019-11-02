#include <stdio.h>
#include <ctype.h>
/*  This is a filter which replaces all non alphabetic characters from a string with a space
    Get a new string,
    check every character in the string for non alphabetic characters,
    replace that character with space,
    print the string
    clear the string*/
int main(int argc, char const *argv[]){
    char a[200] = "";
    while(gets(a) != NULL){
        int i = 0;
        for(i;i < 200;i++){
            char c = *(a+i);
            if(!isalpha(c))*(a+i)=' ';
        }
        for(i = 0;i < 200;i++){
            if((a+i) == NULL) break;
            putc(*(a+i),stdout);
            *(a+i) = 0;
        }
        putc('\n',stdout);
    }
    return 0;
}