#include "adc.h"

void ADC_init(void) {
  // Set reference voltage to AVCC
  ADMUX = (1 << REFS0);
  
  // Enable ADC and set prescaler to 128
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  //set prescaler to 256
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t ADC_read(uint8_t channel) {

  //truncate channel to 0-7 interval (8 channels)
  channel &= 0x07;

  // Select ADC channel pin
  ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
  
  // Start ADC conversion
  ADCSRA |= (1 << ADSC);
  
  // Wait for conversion to complete
  while (ADCSRA & (1 << ADSC));
  
  // Return the converted digital value
  return ADC;
}