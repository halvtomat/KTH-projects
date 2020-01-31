/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


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

bool is_prime(int number){
  for (int i = 2; i <= number/2; i++){
    if(number%i == 0) return false;
  }
  return true;
}

void print_primes(int n){
  for (int i = 2; i < n;i++){
    if(is_prime(i)) print_number(i);
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
