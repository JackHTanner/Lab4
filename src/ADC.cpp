#include "ADC.h"
#include <avr/io.h>

void initADC(){
    //Set up PA0 as input
    DDRA &= ~(1 << DDA0);

    // Enable pull-up resisitor on PA0
    PORTA |= (1 << PORTA0);

    // Set Vref=AVcc
    ADMUX |= (1<<REFS0);

    //Set pre-scaler to 128 and enable ADC 
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}
