#include <util/delay.h>
#include <avr/sleep.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "uart.h"
#include "adc.h"
#include "timers.h"

#define ADC_PIN 7 //a random analog pin
#define OVERFLOW_VALUE 5 //DEBUG!!! 60, perché ogni secondo
#define BUFFER_SIZE 32

static uint8_t overflow_count = 0; // Variable to count overflows of timer
static uint8_t online_mode_counter = 0; // Variable to count seconds in online mode

static uint8_t buffer[BUFFER_SIZE] = {0}; // Buffer to store string data
static int8_t online_mode_value = -1;

// Time struct
Time time = {0}; //initialize all to 0

//Data struct
Data data = {0}; //initialize all to 0

// Timer1 interrupt
ISR(TIMER1_COMPA_vect) {
    overflow_count++;

    if (online_mode_value != -1) {
      online_mode_counter++;
      if (online_mode_counter >= online_mode_value) {
        online_mode_counter = 0;

        //return current minute value
        uint16_t adc_value = ADC_read(ADC_PIN);
        snprintf((char*)buffer, BUFFER_SIZE, "Current value: %d\n", adc_value);
        UART_putString(buffer);
      }
    }

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
    if (received_byte == 'Q') {
        // Send data struct
        UART_putData(&data);
    }
    if (received_byte == 'C') {
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
  setup_timer1();
  //setup_timer2(); TODO: use it to sample current sensor

  UART_putString((uint8_t*)"Online mode? Y (seconds) or N\n");
  UART_getString(buffer);
  if(buffer[0] == 'Y') { // Online mode enabled (seconds)
    online_mode_value = atoi((char*)buffer+2);
    if(online_mode_value <= 0) online_mode_value = -1; // Invalid input
  }
  //end init
  enable_interrupts();

  while(1) {
    // we go to sleep
    sleep_cpu();
  }

}