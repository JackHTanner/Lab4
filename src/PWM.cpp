#include "PWM.h"

void initPWMTimer3(){
    DDRE |= (1<<DDE3);

    TCCR3A |= ((1<<COM3A1) | (1 << WGM30) | (1<<WGM31));
    TCCR3B |= (1 << WGM32) | (1<<CS30);

    OCR3A = ???
}