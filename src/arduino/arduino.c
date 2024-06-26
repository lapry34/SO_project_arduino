#include <util/delay.h>
#include <avr/sleep.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "uart.h"
#include "adc.h"
#include "timers.h"


#define BUFFER_SIZE 512 // Buffer size for UART communication

#define ROOT_TWO 1.41421356237

volatile uint8_t online_mode_counter = 0; // Variable to count seconds in online mode

volatile uint8_t str_buffer[BUFFER_SIZE] = {0}; // Buffer to store string data
volatile uint16_t buffer_len = 0; // Flag to indicate buffer is ready to be sent
volatile int8_t online_mode_value = -1;

volatile uint16_t V_max = 0; // Maximum value of current sensor
volatile uint16_t V_min = 1024; // Minimum value of current sensor

// Time struct
volatile Time time = {0}; //initialize all to 0

//Data struct
volatile Data data = {0}; //initialize all to 0

// Timer1 interrupt, every 1 second
ISR(TIMER1_COMPA_vect) {

    //evaluate the Vrms from Vpp
    uint16_t V_rms = ((V_max-V_min) >> 2) * ROOT_TWO; //(V_max - V_min) / (2 * 1.414);
    process_time(&data, &time, V_rms);

    if (online_mode_value != -1) {
      online_mode_counter++;
      if (online_mode_counter >= online_mode_value) {
        online_mode_counter = 0;

        //put V_rms to buffer to be sent in UART
        memcpy(str_buffer, &V_rms, sizeof(uint16_t));
        str_buffer[sizeof(uint16_t)] = '\n';
        buffer_len = sizeof(uint16_t) + sizeof(char);
      }
    }

    // Reset V_max and V_min
    V_max = 0; 
    V_min = 1024; 
}

// Timer2 interrupt, every 1ms (1kHz)
ISR(TIMER2_COMPA_vect) {
  // Sample current sensor
  uint16_t adc_value = ADC_read(ADC_PIN);

  adc_value > V_max ? V_max = adc_value : V_max; //we update the max value
  adc_value < V_min ? V_min = adc_value : V_min; //we update the min value

}

// UART receive interrupt
ISR(USART_RX_vect) {

    unsigned char received_byte = UDR0;

    PORTB ^= (1 << PORTB5); // Toggle pin 13 on received byte

    // Respond data request
    if (received_byte == 'Q') {
        // put data struct to buffer to be sent in UART
        memcpy(str_buffer, &data, sizeof(Data));
        str_buffer[sizeof(Data)] = '\n'; 
        buffer_len = sizeof(Data) + sizeof(char);
    }
    else if (received_byte == 'C') {
        online_mode_counter = 0; // Reset online mode counter
        memset(&data, 0, sizeof(data)); // Clear data struct
        memset(&time, 0, sizeof(time)); // Clear time struct
    }

}


int main(void){

  //start init
  disable_interrupts();

  UART_init();
  printf_init();
  ADC_init();

  // Set pin 13 as output
  DDRB |= (1 << DDB5);

  // initialize timers
  setup_timer1(); // Timer 1 setup
  setup_timer2(); // Timer 2 setup to sample current sensor at 1kHz

  UART_getString(str_buffer);
  if(str_buffer[0] == 'Y') { // Online mode enabled (seconds)
    online_mode_value = atoi((char*)str_buffer+2);
    if(online_mode_value <= 0) online_mode_value = -1; // Invalid input
  }

  //end init
  enable_interrupts();

  while(1) {
    //we wake up and send the buffer
    if(buffer_len > 0) {
      UART_putBytes(str_buffer, buffer_len);
      memset(str_buffer, 0, BUFFER_SIZE);
      buffer_len = 0;
    }
    // we go to sleep
    sleep_cpu();
  }

}