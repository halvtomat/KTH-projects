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


int timeoutcount = 0; //Global variable used for counting interrupts from the timer2
int mytime = 0x1333;

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

  T2CON = 0x0;                      //Clear the timer control register
  T2CONSET=0x70;                    //Set the prescaling bits to use 1:256 prescaling
  TMR2=0x0;                         //Initialize timer start value to 0
  PR2 = 80000000/256/10;            //Set the timer period to 100ms or 1/10 second using 1:256 prescaling
  T2CONSET = 0x8000;                //Start the timer
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* porte = 0xBF886110;    //Initialize "PORTE" pointer to use the on-board LEDs

  if(IFS(0) & 0x0100){              //If interrupt 8 is requested (Interrupt 8 is used by timer2)
    timeoutcount++;                 //Interrupt 8 is requested everytime timer2 reaches its period
    IFS(0) &= ~0x0100;              //Reset interrupt 8 request
  }

  if(timeoutcount == 10){           //If timeoutcount = 10 (Interrupt 8 is requested 10 times)
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    (*porte)++;                     //Add 1 to the value at "PORTE" for binary counting with the LEDs
    timeoutcount = 0;               //Reset the timeoutcount 
  }
  
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

  //if(mytime == 0x1338) display_image(96,icon); //When time is l33t, display doge
}
