#include <util/delay.h>
#include <avr/sleep.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "uart.h"
#include "adc.h"
#include "timers.h"

#define ADC_PIN 3 //a random analog pin
#define OVERFLOW_VALUE 5 //DEBUG!!! 60, perché ogni secondo
#define BUFFER_SIZE 100 // Buffer size for UART communication

#define SAMPL_FREQ 200 // Sampling frequency 200Hz

static uint8_t online_mode_counter = 0; // Variable to count seconds in online mode
static uint8_t sampling_counter = 0; // Variable to count samples for current sensor

static uint8_t str_buffer[BUFFER_SIZE] = {0}; // Buffer to store string data
static int8_t online_mode_value = -1;

static uint16_t adc_buffer[SAMPL_FREQ] = {0}; // Buffer to store ADC values

// Time struct
Time time = {0}; //initialize all to 0

//Data struct
Data data = {0}; //initialize all to 0

// Timer1 interrupt
ISR(TIMER1_COMPA_vect) {

    // Toggle LED 13
    PORTB ^= (1 << PORTB5);

    //evaluate the mean of the samples
    uint16_t adc_value = 0;
    for(uint8_t i = 0; i < SAMPL_FREQ; i++){
        adc_value += (adc_buffer[i] / SAMPL_FREQ); //we divide by the number of samples to avoid overflow
    }
    memset(&adc_buffer, 0, sizeof(adc_buffer)); // Clear ADC buffer, Probabilmente non serve, ragionare

    process_time(&data, &time, adc_value);

    if (online_mode_value != -1) {
      online_mode_counter++;
      if (online_mode_counter >= online_mode_value) {
        online_mode_counter = 0;

        //print the current value to the UART (online mode)
        snprintf((char*)str_buffer, BUFFER_SIZE, "[ONLINE] Current value: %d\n", adc_value);
        UART_putString(str_buffer);
      }
    }
}

ISR(TIMER2_COMPA_vect) {
    // Sample current sensor
    adc_buffer[sampling_counter] = ADC_read(ADC_PIN);
    sampling_counter++;

    if (sampling_counter >= SAMPL_FREQ) {
        sampling_counter = 0;
    }
}

// UART receive interrupt
ISR(USART_RX_vect) {
    disable_interrupts();

    unsigned char received_byte = UDR0;

    PORTB ^= (1 << PORTB5); // Toggle pin 13 on received byte

    // Respond data request
    if (received_byte == 'Q') {
        // Send data struct
        UART_putData(&data);
    }
    if (received_byte == 'C') {
        sampling_counter = 0; // Reset sampling counter
        online_mode_counter = 0; // Reset online mode counter
        memset(&adc_buffer, 0, sizeof(adc_buffer)); // Clear ADC buffer
        memset(&data, 0, sizeof(data)); // Clear data struct
        memset(&time, 0, sizeof(time)); // Clear time struct
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
  setup_timer1(); // Timer 1 setup
  setup_timer2(); // Timer 2 setup to sample current sensor at 200 Hz

  UART_putString((uint8_t*)"Online mode? Y (seconds) or N\n");
  UART_getString(str_buffer);
  if(str_buffer[0] == 'Y') { // Online mode enabled (seconds)
    online_mode_value = atoi((char*)str_buffer+2);
    if(online_mode_value <= 0) online_mode_value = -1; // Invalid input
  }
  //end init
  enable_interrupts();

  while(1) {
    // we go to sleep
    sleep_cpu();
  }

}