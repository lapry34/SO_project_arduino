#pragma once

#include <avr/interrupt.h>

//enable and disable interrupts functions
void enable_interrupts(void);
void disable_interrupts(void);

#define NUM_MINUTES 60
#define NUM_HOURS 24
#define NUM_DAYS 30
#define NUM_MONTHS 12

// Struct to store the averages
typedef struct {
    float minutes[NUM_MINUTES];
    float hourly[NUM_HOURS];
    float daily[NUM_DAYS];
    float monthly[NUM_MONTHS];
    float yearly;
} Data;