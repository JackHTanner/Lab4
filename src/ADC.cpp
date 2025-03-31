#include "ADC.h"
#include <avr/io.h>

void initADC(){
    //Set up PF0 as input
    DDRF &= ~(1 << DDF0);

    // Enable pull-up resisitor on PF0
    PORTF |= (1 << PORTF0);

    // Set Vref=AVcc
    ADMUX |= (1<<REFS0);        // AVCC with external capacitor at AREF pin

    // Set right justification
    ADMUX &= !(1<<ADLAR);

    //Set pre-scaler to 128 and enable ADC 
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t readADC(){
    // Start conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));
    
    // Return the 10-bit ADC result
    return ADC;
}