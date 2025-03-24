#include "timer.h"

void initTimer0(){

    // Settings Timer 0 to CTC mode
    TCCR0A &= ~(1<<WGM00);
    TCCR0A |= (1<<WGM01);
    TCCR0B &= ~(1<<WGM02);
}

void delayUs(unsigned int delay){
    unsigned int count = 0;

    // Need to find MAX count value for CTC mode
    // M (count) = (1us * 16MHz) / 1 = 16
    OCR0A = 16;

    // Turning on timer with prescalar = 1
    TCCR0B &= ~((1<<CS02) | (1<<CS01));
    TCCR0B |= (1<<CS00);

    while(count < delay){ //if we still need to delay by more miliseconds
       
        TIFR0 |= (1 << OCF0A); //this sets the CTC flag down, so that we can start a new clock delay (flag down is logic 1)
        TCNT0 = 0; //clears the timer      
       
        //while flag is down do not do anything
        while(!(TIFR0 & (1 << OCF0A))); //!number is equivalent to number != 0
        //when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        count++; //increment counter
    }
    

    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); //turns timer off
}

void initTimer1(){
    //To set into CTC mode, we need WGM13 to be 0, WGM12 to be 1, WGM11 to 0, WGM10 to be 0
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
}

void delayS(unsigned int delay){
    unsigned int count = 0;

    //want a time delay of 1 us, so count = (Time delay * frequency of clock)/Prescalar
    //Count (M) = (1s * 16MHz)/1024 - 1 = 15,624

    //Need to interface a 16 bit module, which means writing the high byte first, then the low byte
    //16 in hex is 00 10
    OCR1A = 15624;
    

    //Turn on timer with prescalar 1024 (bits 1 0 1)
    TCCR1B &= ~(1 << CS11);
    TCCR1B |= ((1 << CS10) | (1 << CS12)); //by setting CS12 CS11 CS10 to 001, turn on clock

    while(count < delay){ //while count is less than delay
        
        //Sets the timer flag to 1
        TIFR1 |= (1 << OCF1A); //logic 1 is flag down
        
        //Set the timer register to 0
        TCNT1 = 0;

        //while flag is down do not do anything
        while(!(TIFR1 & (1 << OCF1A))); //!number is equivalent to number != 0
        //when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        count++; //1 microsecond delay as been achieved, go to next microsecond
    }

    //turn timer off
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

}