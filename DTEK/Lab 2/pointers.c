


#include <stdio.h>
#include <stdlib.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int count;
int* list1;
int* list2;

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}
void copycodes(char* a, int* b, int* c){
  while(a[0] != 0){
    *b = *a;
    a++;
    b++;
    *c = *c + 1;
  }
}

void work(){
  copycodes(text1,list1,&count);
  copycodes(text2,list2,&count);
}

int main(void){
  list1 = (int *)malloc(80);
  list2 = (int *)malloc(80);
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
  free(list1);
  free(list2);
}