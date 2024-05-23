#pragma once

#include <stdint.h>

#include <avr/io.h>

//init adc
void ADC_init(void);

//read from adc channel
uint16_t ADC_read(uint8_t channel);