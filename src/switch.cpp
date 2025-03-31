// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3(){
 DDRB &= ~(1<<DDB3); // enables input on pin 50
 PORTB |= (1<<PORTB3); // enables pull up resistor on pin 50

 PCICR |= (1 << PCIE0);
 PCMSK0 |= (1 << PCINT3);
}
