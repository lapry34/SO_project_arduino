#pragma once

#include <avr/interrupt.h>

#define MINUTES 60
#define HOURS 24
#define DAYS 30
#define MONTHS 12

// Struct to store the time averages
typedef struct {
    float minutes[MINUTES];
    float hourly[HOURS];
    float daily[DAYS];
    float monthly[MONTHS];
    float yearly;
} Data;

//enable and disable interrupts functions
void enable_interrupts(void);
void disable_interrupts(void);

//process time and returns true if the hour has changed
uint8_t process_time(uint8_t *minutes, uint8_t *hours, uint8_t *days, uint8_t *months, uint8_t *years);