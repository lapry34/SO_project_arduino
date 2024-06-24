#pragma once

#include <stdint.h>

#include <avr/io.h>

#define ADC_PIN 3 //a random analog pin

//init adc
void ADC_init(void);

//read from adc channel
uint16_t ADC_read(uint8_t channel);