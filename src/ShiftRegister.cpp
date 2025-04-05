#include "ShiftRegister.h"
#include <avr/io.h>
#include <Arduino.h>
#include "timer.h"


byte numbers[10] = {
  //0GFEDCBA
  0b00111111, // 0: a,b,c,d,e,f
  0b00000110, // 1: B,C
  0b01011011, // 2: A,B,D,E,G
  0b01001111, // 3: A,B,C,D,G
  0b01100110, // 4: B,C,F,G
  0b01101101, // 5: A,C,D,F,G
  0b01111101, // 6: A,C,D,E,F,G
  0b00000111, // 7: A,B,C
  0b01111111, // 8: A,B,C,D,E,F,G (all segments)
  0b01101111  // 9: A,B,C,D,F,G (all except E)
};

void setup() {
  DDRB |= (1 << DDB3); // latch pin
  DDRB |= (1 << DDB1); // data pin
  DDRB |= (1 << DDB4); // clock pin
}

void countdown() {
  for(int i = 9; i >= 0; i--) {
    setDisplay(i);
    delayS(1);  // Delay AFTER setting display
  }
}

void setDisplay(byte digit) {
  // Set the latch pin to LOW
  PORTB &= ~(1 << PORTB3);
  
  // Send bits (MSB first)
  for (int i = 7; i >= 0; i--) {
    if (numbers[digit] & (1 << i)) {  //traverse through digit, if current bit is high, set data high & vice versa
      PORTB |= (1 << PORTB1);    // Set data pin HIGH
    } else {
      PORTB &= ~(1 << PORTB1);   // Set data pin LOW
    }
    
    PORTB |= (1 << PORTB4);      // Set clock pin HIGH
    delayUs(1);             // Small delay to ensure clock pulse
    PORTB &= ~(1 << PORTB4);     // Set clock pin LOW
  }
  
  PORTB |= (1 << PORTB3);        // Set the latch pin to HIGH
}

