/*
Author: Jack Tanner
Date: 3/17/2025
Assignment: Lab 3, ECE 372
*/

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void delayS(unsigned int delay);
void initTimer0();
void delayUs(unsigned int delay); 


#endif