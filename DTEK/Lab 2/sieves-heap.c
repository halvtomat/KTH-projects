#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLUMNS 6
int column = 0;

void print_number(int number){
  printf("%10d",number);
  column++;
  if(column%COLUMNS==0) printf("\n");
}

void print_sieves(int max){
	bool *a = (bool *)malloc(max+1);
	for(int i = 2;i <= max; i++){
		a[i] = true;
	}

	for (int i = 2; i*i <= max; i++){
		if(a[i]){
			for (int j = i*i; j <= max; j = j+i){
				a[j] = false;
			}
		}
	}

	for (int i = 2; i <= max; i++){
		if (a[i]) print_number(i);
	}
	free(a);
}

int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}