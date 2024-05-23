#include <util/delay.h>
#include <avr/sleep.h>
#include <stdio.h>

#include "utils.h"
#include "uart.h"
#include "adc.h"

#define MAX_BUF 256
#define ADC_PIN 7 //a random analog pin
#define OVERFLOW_VALUE 1 //DEBUG!!! 14 //così so 58 secondi e qualcosa

static uint8_t buf[MAX_BUF]; // Buffer for UART
static uint8_t overflow_count = 0; // Variable to count overflows of timer

// Time variables
static uint8_t minutes = 0;
static uint8_t hours = 0;
static uint8_t days = 0;
static uint8_t months = 0;
static uint8_t years = 0;

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


ISR(TIMER1_COMPA_vect) {
    overflow_count++;
    if (overflow_count >= OVERFLOW_VALUE) {  // Check for overflows
      overflow_count = 0;                    // Reset overflow count

      // Do something every minute
      // For example, toggle the LED on pin 13
      PORTB ^= (1 << PORTB5);

      //read from ADC and print the value
      uint16_t adc_value = ADC_read(ADC_PIN);
      uint8_t flag_process = process_time(&minutes, &hours, &days, &months, &years);
      
      sprintf((char*) buf, "minute: %d, ADC value: %d\n", minutes, adc_value);
      sprintf((char*) buf, "minute: %d, hour: %d, day: %d, month: %d, year: %d\n", minutes, hours, days, months, years);
      UART_putString(buf);

      if(flag_process == 0) minutes++; // Increment minute count
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

  UART_putString((uint8_t*)"Buongiornissimo sono quello simpaticissimo\n");

  while(1) {
    // we go to sleep
    sleep_cpu();
  }

}