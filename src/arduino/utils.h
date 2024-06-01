#pragma once

#include <avr/interrupt.h>

#define SECONDS 60
#define MINUTES 60
#define HOURS 24
#define DAYS 30
#define MONTHS 12

// Struct to store the time averages
typedef struct {
    uint16_t seconds[SECONDS];
    uint16_t minutes[MINUTES];
    uint16_t hourly[HOURS];
    uint16_t daily[DAYS];
    uint16_t monthly[MONTHS];
    uint16_t yearly;
} __attribute__((packed)) Data;

//struct to store time values
typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t days;
    uint8_t months;
    uint8_t years;
} Time;

//enable and disable interrupts functions
#define enable_interrupts() sei()
#define disable_interrupts() cli()

//process time
void process_time(Data *data, Time *time, uint16_t adc_value);