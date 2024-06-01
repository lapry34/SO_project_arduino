#pragma once

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>

#include "utils.h"

#define BAUD 57600
#define MYUBRR (F_CPU/16/BAUD-1)

//initialize UART
void UART_init(void);
void printf_init(void);

//receive data functions
uint8_t UART_getChar(void);
uint8_t UART_getString(uint8_t* buf);

//send data functions
void UART_putString(uint8_t* buf);
void UART_putChar(uint8_t c);
int UART_putChar_printf(char var, FILE *stream);

//custom function to send bytes
void UART_putBytes(void* buf, uint8_t len);