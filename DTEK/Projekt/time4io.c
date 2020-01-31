#include <stdint.h>
#include <pic32mx.h>
#include "tamagotchi.h"

int getsw(void){
  int result=0xf&(PORTD >> 8);	//Shift the 4 SW input bits to be the least significant 
  return result;				//then mask out all other bits and return
}
int getbtns(void){
  int result=0x7&(PORTD >> 5);	//Shift the 3 BTN inout bits to be the least significant
  return result;				//then mask out all other bits and return
}
