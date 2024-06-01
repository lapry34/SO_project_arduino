#include <util/delay.h>
#include <avr/sleep.h>
#include <stdio.h>

#include "utils.h"
#include "uart.h"
#include "adc.h"
#include "timers.h"

#define ADC_PIN 7 //a random analog pin
#define OVERFLOW_VALUE 1 //DEBUG!!! 14 //così so 58 secondi e qualcosa

static uint8_t overflow_count = 0; // Variable to count overflows of timer

// Time struct
Time time = {0}; //initialize all to 0

//Data struct
Data data = {0}; //initialize all to 0

// Timer1 interrupt
ISR(TIMER1_COMPA_vect) {
    overflow_count++;
    if (overflow_count >= OVERFLOW_VALUE) {  // Check for overflows
      overflow_count = 0;                    // Reset overflow count

      //read from ADC and print the value
      uint16_t adc_value = ADC_read(ADC_PIN);
      uint8_t flag_process = process_time(&data, &time, adc_value);

      if(flag_process == 0) time.minutes++; // Increment minute count
    }

}

ISR(TIMER2_COMPA_vect) {
    // Toggle LED 13
    PORTB ^= (1 << PORTB5);
}

// UART receive interrupt
ISR(USART_RX_vect) {
    disable_interrupts();

    unsigned char received_byte = UDR0;

    PORTB ^= (1 << PORTB5); // Toggle pin 13 on received byte

    // Respond data request
    if (received_byte == 'R') {
        // Send data struct
        UART_putData(&data);
    }

    enable_interrupts();
}


int main(void){

  //start init
  disable_interrupts();

  UART_init();
  ADC_init();

  // Set pin 13 as output
  DDRB |= (1 << DDB5);

  // initialize timers
  setup_timer1();
  //setup_timer2(); TODO: use it to sample current sensor

  //end init
  enable_interrupts();

  while(1) {
    // we go to sleep
    sleep_cpu();
  }

}