#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLUMNS 6
int column = 0;

void print_number(float number){
  printf("%10f",number);
  column++;
  if(column%COLUMNS==0) printf("\n");
}

void mean_sieves(int max, bool a[]){
	float mean = 0;
	int k = 0;
	for (int i = 2;i <= max; i++){
		if (a[i]){
			k++;
		 	mean = mean + i;
		}
	}
	print_number(mean/k);
}

void print_sieves(int max){
	bool a[max+1];
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
	mean_sieves(max,a);
}

int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}