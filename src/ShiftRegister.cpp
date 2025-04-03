#include "ShiftRegister.h"
#include "timer.h"
#include <avr/io.h>
#include <Arduino.h>

const int latchPin = 11;
const int clockPin = 9;
const int dataPin = 12;

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
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
}

// Loop from 9 to 0, delay 1 second between 
// each iteration
void loop() {
    for(byte i = 9; i >= 0; --i) {
        delayS(1);
        setDisplay(i); 
    }
    delayS(1);
}

// Display a particular number (9, 8,...0)
// on the 7seg display
void setDisplay(byte digit) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, numbers[digit]);
    digitalWrite(latchPin, HIGH);
}
