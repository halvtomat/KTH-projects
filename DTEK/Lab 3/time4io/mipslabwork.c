/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trise = 0xBF886100; //Initialize "TRISE" pointer to mask PORT-E
  (*trise) &= ~0xFF;                //Set bits 7-0 to 0 for output in PORT-E
  TRISD &= 0xFE0;                   //Set bits 11-5 to 1 for input in PORT-D
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* porte = 0xBF886110;    //Initialize "PORTE" pointer to use the on-board LEDs
  delay( 1000 );                       
  time2string( textstring, mytime );   
  display_string( 3, textstring );     
  display_update();
  tick( &mytime );
  (*porte)++;                          //Add 1 to the value at "PORTE" for binary counting with the LEDs
  display_image(96, icon);
  int buttons = getbtns();             //Set int "buttons" to return of "getbtns"
  int switches = getsw();              //Set int "switches" to return of "getsw"
  if(buttons == 1 || buttons == 3 || buttons == 5 || buttons == 7){   //If BTN2 is pressed
    int temp = switches<<4;            //Shift the "switches" value to the right position
    int maskTime = 0xff0f&mytime;      //Set the byte we are about to change to 0
    mytime = maskTime + temp;          //Set the byte we want to change to its new value
    }
  if(buttons == 2 || buttons == 3 || buttons == 6 || buttons == 7){   //If BTN3 is pressed
    int temp = switches<<8;            //Shift the "switches" value to the right position
    int maskTime = 0xf0ff&mytime;      //Set the byte we are about to change to 0
    mytime = maskTime + temp;          //Set the byte we want to change to its new value
  }
  if(buttons == 4 || buttons == 5 || buttons == 6 || buttons == 7){   //If BTN4 is pressed
    int temp = switches<<12;           //Shift the "switches" value to the right position
    int maskTime = 0x0fff&mytime;      //Set the byte we are about to change to 0
    mytime = maskTime + temp;          //Set the byte we want to change to its new value
  }
}
