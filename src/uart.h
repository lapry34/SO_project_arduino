#pragma once

#include <stdint.h>

#include <avr/io.h>

#define BAUD 19600
#define MYUBRR (F_CPU/16/BAUD-1)

//initialize UART
void UART_init(void);

//receive data functions
uint8_t UART_getChar(void);
uint8_t UART_getString(uint8_t* buf);

//send data functions
void UART_putString(uint8_t* buf);
void UART_putChar(uint8_t c);