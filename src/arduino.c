#include <util/delay.h>
#include <stdio.h>

#include "utils.h"
#include "uart.h"
#include "adc.h"

#define MAX_BUF 256



int main(void){

  //start init
  disable_interrupts();

  UART_init();
  ADC_init();


  //end init
  enable_interrupts();


  UART_putString((uint8_t*)"write something, i'll repeat it\n");
  uint8_t buf[MAX_BUF];
  while(1) {

    // Read from ADC channel 7
    uint16_t adc_value = ADC_read(7);
    // Print the value into a string buffer
    sprintf(buf, "ADC value: %d\n", adc_value);
    UART_putString(buf);
  }
}