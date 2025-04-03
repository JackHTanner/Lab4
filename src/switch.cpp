// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3(){
 DDRD &= ~(1<<DDD0); // enables input on pin 21
 PORTD |= (1<<PORTD0); // enables pull up resistor on pin 21


 EICRA |= (1 << ISC00);
 EICRA &= ~(1 << ISC01);
 PCICR |= (1 << PCIE0);
 EIMSK |= (1 << INT0);
}
