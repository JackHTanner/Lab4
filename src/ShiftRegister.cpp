#include "ShiftRegister.h"
#include "timer.h"
#include <avr/io.h>
#include <Arduino.h>

// Function declarations
void setDisplay(byte digit);

// Binary values that map to each
// segment (a, b,..., g) of the 7seg display
byte numbers[10] = {
  0b01111011, // 0
  0b00001001, // 1
  0b10110011, // 2
  0b10011011, // 3
  0b11001001, // 4
  0b11011010, // 5
  0b11111000, // 6
  0b00001011, // 7
  0b11111011, // 8
  0b11001011, // 9
};

// Set the latch pin, data pin,
// and clock pin of SR as outputs
void setup() {
  DDRB |= (1 << DDB3); // latch pin
  DDRB |= (1 << DDB1); // data pin
  DDRB |= (1 << DDB4); // clock pin
}

// Loop from 9 to 0, delay 1 second between
// each iteration
void loop() {
  for(int i = 9; i >= 0; i--) {
    delayS(1);
    setDisplay(i);
  }
  delayS(1);
}

// Display a particular number (9, 8,...0)
// on the 7seg display
void setDisplay(byte digit) {
  // Set the latch pin to LOW
  PORTB &= ~(1 << PORTB3);
  
  for (int i = 0; i < 8; i++) {
    if (numbers[digit] & (1 << i)) {
      PORTB |= (1 << PORTB1);  // Set data pin HIGH
    } else {
      PORTB &= ~(1 << PORTB1); // Set data pin LOW
    }
    PORTB |= (1 << PORTB4);    // Set clock pin HIGH
    delayUs(1);
    PORTB &= ~(1 << PORTB4);   // Set clock pin LOW
  }
  
  PORTB |= (1 << PORTB3);      // Set the latch pin to HIGH
}
