#include "ADC.h"
#include <avr/io.h>

void initADC(){

  // 1. ADC MUX register set reference voltage set to AVCC = 5V output. 
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);
   // 2. ADCH &ADCL Setting
  // determine left or right justified (ADLAR = 0 RIGHT JUSTIFIED)
  ADMUX &= ~(1 << ADLAR);

  // 3. Choose Analog Pin for I/P
  // Specify ADC input channel and mode
  //Set ADC7 as single-ended input with MUX[5:0] = 0b000111
  // 2. Select ADC0 (A0) by clearing all MUX bits
  ADMUX &= ~((1<<MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
  ADCSRB &= ~(1 << MUX5);

  // 4. enable ADC and 5. enable auto-triggering
  ADCSRA|= (1 << ADEN) | (1 << ADATE);

  // 6. set Auto Trigger Source Selection
  // Use free-running mode ADTS[2:0] = 0b000 
  ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));


   // 7. ADC Sample Rate/ Frequency
  // set the ADC clock frequemcy.  Use a pre-scaler of 128
  // ADC clock frequency is 16 Mhz divided by pre-scaler = 125KHz
  // Sampling rate is 1/ ((1/125K Hz )*(13 clock cycles)) = 9615 KHz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  

  //8.  disable ADC0 pin digital input - pin A0 on board
  DIDR0 |= (1 << ADC0D);

  // 9. start the first ADC conversion
  ADCSRA |= ( 1 << ADSC);
}

uint16_t readADC() {
  // Wait for conversion to complete
  while (!(ADCSRA & (1 << ADIF)));  // Wait for ADIF to be set
  
  // Clear the ADC interrupt flag by writing 1 to it
  ADCSRA |= (1 << ADIF);

  // Return the 10-bit ADC result
  return ADC;
}