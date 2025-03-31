#include "PWM.h"

void initPWMTimer3(){

    TCCR3A |= ((1<<COM3A1) | (1 << WGM30) | (1<<WGM31));
    TCCR3B |= (1 << WGM32) | (1<<CS30);

    DDRH |= (1<<DDH5);

    ICR3 = 39999;

    OCR3A = 0;
}

void changeDutyCycle(uint16_t adcValue){
    OCR3A = (adcValue*ICR3) / 1023;
}