#include "SevenSegment.h"
#include <avr/io.h>

void initSevenSegment() {
    // Set the DDRB to output
    DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5) | (1 << DDC6);
    // Set the PORTC to pull up resistors
    //PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6) | (1<<PORTC7);
}

void displayDigit(int digit) {
    switch (digit) {
        case 0:
            PORTC = 0b00111111;
            break;
        case 1:
            PORTC = 0b00000110;
            break;
        case 2:
            PORTC = 0b01011011;
            break;
        case 3:
            PORTC = 0b01001111;
            break;
        case 4:
            PORTC = 0b01100110;
            break;
        case 5:
            PORTC = 0b01101101;
            break;
        case 6:
            PORTC = 0b01111101;
            break;
        case 7:
            PORTC = 0b00000111;
            break;
        case 8:
            PORTC = 0b01111111;
            break;
        case 9:
            PORTC = 0b01101111;
            break;
        default:
            PORTC = 0b00000000;
            break;
    }
}
