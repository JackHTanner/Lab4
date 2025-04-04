// Author: Jack Tanner, Eryc Rod, Davron, Ketar
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
#include "ADC.h"


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
  // Serial monitor testing
  Serial.begin(9600);
  Serial.flush();
  initTimer1();
  initSwitchPB3();
  initPWMTimer3();
  initTimer0();
  initSevenSegment();
  initADC();
  sei(); // Enable global interrupts.

  unsigned int countDown = 9;
  uint16_t adcValue;

  Serial.println("Initializing");
  while (1) {
    switch(buttonState){
      case wait_disabled:
      PORTB &= ~(1<<PORTB6);
      PORTB &= ~(1<<PORTB7);
      OCR3B = 0;
      countDown = 9;
        cli();
          for (int i = countDown; i >= 0; i--){
            displayDigit(i);
            delayS(1);
          }
          displayDigit(-1);
          sei();
          buttonState = wait_press; // Reset counter
        break;
      case wait_press:
        sei();
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

  adcValue = readADC();
  Serial.println(adcValue);
  changeDutyCycle(adcValue);

  // Increment or decrement count depending on the direction

// while loop
}
  return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/
ISR(INT0_vect){
  if(buttonState == wait_press){
    buttonState = debounce_press;
  }
  else if(buttonState == wait_release){
    buttonState = debounce_release;
  }
}
