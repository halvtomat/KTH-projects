/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "tamagotchi.h"  /* Declatations for this projekt */
#include <stdbool.h>

int timeoutcount = 0; //Global variable used for counting interrupts from the timer2
int startedEating;


struct PIG{
  bool isAlive;
  bool isSleeping;
  bool isEating;
  bool isPlaying;
  int health;
  int hunger;
  int tiredness;
  int timeAlive;
  int happiness;
};

 struct PIG pig = {1,0,0,0,100,0,0,0,100};                   //Initialize PIG pig with standard values

/* Interrupt Service Routine */
void user_isr( void ) {
  if(IFS(0) & 0x100){               //If interrupt 8 is requested (Interrupt 8 is used by timer2)
    timeoutcount++;                 //Interrupt 8 is requested everytime timer2 reaches its period
    IFS(0) &= ~0x100;               //Reset interrupt 8 request
  }

  if(timeoutcount %1 == 0){
    display_update();
    if(pig.isEating == false){
      startedEating = timeoutcount;
    }

    if(pig.isAlive){
      display_trait(0,itoaconv(pig.hunger)); 
      display_trait(1,itoaconv(pig.tiredness));  
      display_trait(2,itoaconv(pig.happiness));       
      display_trait(3,itoaconv(pig.timeAlive));
      if(pig.isSleeping){
        display_image(96,pig_sleeping);
      }else if (pig.isPlaying){
         display_image(96,playing);
      }
      else if(pig.isEating){
        display_image(96,soup);
        if(timeoutcount - startedEating == 30){
          pig.hunger = 0;
          pig.isEating = false;
        }
      }else{
        if(pig.hunger > 50 && pig.tiredness > 50 && pig.happiness < 30){
          display_image(96,pig_hungry_sad_tired);
        }else if(pig.hunger > 50 && pig.happiness < 30){
          display_image(96,pig_hungry_sad);
        }else if(pig.hunger > 50 && pig.tiredness > 50){
          display_image(96,pig_hungry_tired);
        }else if(pig.happiness <30 && pig.tiredness > 50){
          display_image(96,pig_sad_tired);
        }else if(pig.hunger > 50){
          display_image(96,pig_hungry);
        }else if(pig.happiness < 30){
          display_image(96,pig_sad);
        }else if(pig.tiredness > 50){
          display_image(96,pig_tired);
        }else{
          display_image(96,pig_standard);
        }
      }
    }else{
      display_clear();
      display_image(96,pig_dead);
      display_string(0,"RIP PIG!!!");
      display_string(1,"RIP PIG!!!");
      display_string(2,"RIP PIG!!!");
      display_string(3,"RIP PIG!!!");
    }
  }


  if(timeoutcount %5 == 0 && pig.isAlive){           //Pigs traits wont update if pig is dead, hunger increases
                                                    //faster than tiredness when pig is awake

    if(pig.hunger < 100 && pig.isSleeping == false && pig.isEating == false){     
      pig.hunger++;
    }
    if(pig.isSleeping == 1 && pig.tiredness > 0){   //Tiredness decreases faster when pig is sleeping than it
      pig.tiredness--;                              //increases when pig is awake
    }
    if(pig.isPlaying && pig.happiness <100){
      pig.happiness++;
    }    
  }

  if(timeoutcount %10 == 0 && pig.isAlive){             
    if(pig.isSleeping == 0 && pig.tiredness < 100){
      pig.tiredness++;
    }
    if(pig.tiredness == 100 && pig.isSleeping == false && pig.health > 0){    //Pig health always updates at a slower rate
      pig.health--;                                                       //than hunger or tiredness
    } else if(pig.isSleeping == 1 && pig.hunger < 75 && pig.health < 100){
      pig.health++;
    }
    if(pig.hunger == 100 && pig.health > 0){
      pig.health--;
    }
    if(pig.hunger < 100 && pig.isSleeping){
      pig.hunger++;
    }
  }
  if(timeoutcount %15 == 
  0 && pig.isAlive && pig.happiness > 0 && pig.isPlaying == false){ //Updating the pig's happiness
    pig.happiness--;
  }
  if(timeoutcount %10 == 0 && pig.isAlive){             //Every second update time alive for pig
    pig.timeAlive++;
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  spawnPig();

  TRISE &= 0xFF;                    //Set bits 7-0 to 0 for output in PORT-E
  TRISD &= 0xFE0;                   //Set bits 11-5 to 1 for input in PORT-D

  T2CON = 0x0;                      //Clear the timer control register
  T2CONSET=0x70;                    //Set the prescaling bits to use 1:256 prescaling
  TMR2=0x0;                         //Initialize timer start value to 0
  PR2 = 80000000/256/10;            //Set the timer period to 100ms or 1/10 second using 1:256 prescaling
  T2CONSET = 0x8000;                //Start the timer

  IECSET(0) = 0x900;                //Enable interrupt 8 (used by timer2)
  IPCSET(2) = 0x1F;                 //Set timer2 to highest possible priority
  enable_interrupt();               //Enable interrupts globally
  return;
}

void spawnPig(){                    //When the pig is dead but you want it alive, call this
  display_clear();
  //For displaying traits
  display_string(0,"Hunger: ");     
  display_string(1,"Tireds: ");
  display_string(2,"Happy: ");
  display_string(3,"Alive:  ");
  
  //Initialize pig values, isAlive last
  pig.health = 100;
  pig.hunger = 0;
  pig.tiredness = 0;
  pig.happiness = 100;
  pig.timeAlive = 0;
  pig.isEating = false;
  pig.isSleeping = false;
  pig.isPlaying = false;
  pig.isAlive = true;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  
  if(pig.health == 0){
    pig.isAlive = false;
  }

//----------------------------Health Leds segment-----------------------------
//This switch statement will display 
//the pigs health using the green LEDs on the basic I/O shield
  int health_leds = 8;
  if (pig.health <= 100 && pig.health > 87) {
    health_leds = 8;
  }else if (pig.health <= 87 && pig.health > 75) {
    health_leds = 7;
  }else if (pig.health <= 75 && pig.health > 62) {
    health_leds = 6;
  }else if (pig.health <= 62 && pig.health > 50) {
    health_leds = 5;
  }else if (pig.health <= 50 && pig.health > 37) {
    health_leds = 4;
  }else if (pig.health <= 37 && pig.health > 25) {
    health_leds = 3;
  }else if (pig.health <= 25 && pig.health > 12) {
    health_leds = 2;
  }else if (pig.health <= 12 && pig.health > 0) {
    health_leds = 1;
  }else if (pig.health == 0){
    health_leds = 0;
  }

  switch(health_leds){
    case 8:
      PORTE = 0xFF;
      break;
    case 7:
      PORTE = 0x7F;
      break;
    case 6:
      PORTE = 0x3F;
      break;
    case 5:
      PORTE = 0x1F;
      break;
    case 4:
      PORTE = 0x0F;
      break;
    case 3:
      PORTE = 0x07;
      break;
    case 2:
      PORTE = 0x03;
      break;
    case 1:
      PORTE = 0x01;
      break;
    case 0:
      PORTE = 0x00;
      break;
  }
//------------------------Health leds segment end------------------------------



//------------------------Buttons segment--------------------------------------
//This segment will handle all buttonpresses 
  int buttons = getbtns();             //Set int "buttons" to return of "getbtns"
  int switches = getsw();              //Set int "switches" to return of "getsw"

  bool buttonpressed;

  if(buttons == 1){   //If BTN2 is pressed
    pig.happiness = 0;
    pig.hunger = 100;
    pig.tiredness = 100;
  }
  if(buttons == 2 && pig.isAlive == false){   //If BTN3 is pressed
    spawnPig();
  }
  if(buttons == 4 && buttonpressed == false && pig.isSleeping == false && pig.isPlaying == false && pig.happiness >30){   //If BTN4 is pressed
    buttonpressed = true;
    pig.isEating = true;
  }
  if(switches & 2 && pig.isEating == false && pig.isPlaying== false && pig.happiness > 30){
    pig.isSleeping = true;
  }else{
    pig.isSleeping = false;
  }
  if(switches & 4 && pig.isEating == false && pig.isSleeping == false){
    pig.isPlaying = true;
  }else{
    pig.isPlaying = false;
  }
  if(switches & 1){
    pig.isAlive = false;        //Kill Switch
    pig.health  = 0;
  }
}
//----------------------Buttons segment end------------------------------------