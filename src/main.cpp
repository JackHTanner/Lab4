// Author:
// Net ID:
// Date:
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//




#include "Arduino.h"
#include <avr/io.h>
#include "switch.h"
#include "timer.h"
#include "PWM.h"




/*
 * Define a set of states that can be used in the state machine using an enum.
 */
// typedef enum .......


// Initialize states.  Remember to use volatile 


typedef enum stateName {
  wait_disabled, wait_press, debounce_press, wait_release, debounce_release
 } State;

 volatile State buttonState = wait_press;



int main(){

  bool countDone = 0;

  unsigned int i = 0;
  initTimer1();
  initSwitchPB3();
  initTimer0();
  sei(); // Enable global interrupts.
  unsigned char countDown = 9;

  while (1) {
    switch(buttonState){
      case wait_disabled:
        delayS(10);
        buttonState = wait_press;
        break;
      case wait_press:
        break;
      case debounce_press:
        delayUs(1);
        buttonState = wait_release;
        break;
      case wait_release:
        break;
      case debounce_release:
        delayUs(1);
         buttonState = wait_disabled;
        break;
      default:
        break;
    }
  IncFrequency(1000);

  // Increment or decrement count depending on the direction
  if (countDown >= 0) {
      countDown--; // Count up
  } else {
      buttonState = wait_press; // Reset counter

  }

// while loop
}
  return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/
ISR(PCINT0_vect){
  if(buttonState == wait_press){
    buttonState = debounce_press;
  }
  else if(buttonState == wait_release){
    buttonState = debounce_release;
  }
}