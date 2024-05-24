#include <util/delay.h>
#include <avr/sleep.h>
#include <stdio.h>

#include "utils.h"
#include "uart.h"
#include "adc.h"

#define ADC_PIN 7 //a random analog pin
#define OVERFLOW_VALUE 1 //DEBUG!!! 14 //così so 58 secondi e qualcosa

static uint8_t overflow_count = 0; // Variable to count overflows of timer

// Time struct
Time time = {0}; //initialize all to 0

//Data struct
Data data = {0}; //initialize all to 0

// Timer setup
void setup_timer(void) {

    // Set Timer to CTC (Clear Timer on Compare Match) mode
    TCCR1A = 0; 
    TCCR1B |= (1 << WGM12);

    // Set the Compare Match Register for 1 minute
    // Assuming a 16 MHz clock and a prescaler of 1024

    OCR1A = 65535; // Count to 65535, the maximum value of a 16-bit register!
    //we have to overflow and count to get a minute!

    OCR1A = 300; //DEBUG!!! TOGLIERE!!!!

    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Start Timer1 with prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    return;
}

// Timer interrupt
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

// UART receive interrupt
ISR(USART_RX_vect) {
    unsigned char received_byte = UDR0;

    PORTB ^= (1 << PORTB5); // Toggle pin 13 on received byte

    // Respond data request
    if (received_byte == 'R') {
        // Send data struct
        UART_putData(&data);
    }
}


int main(void){

  //start init
  disable_interrupts();

  UART_init();
  ADC_init();

  // Set pin 13 as output
  DDRB |= (1 << DDB5);

  // initialize timer
  setup_timer();

  //end init
  enable_interrupts();

  while(1) {
    // we go to sleep
    sleep_cpu();
  }

}