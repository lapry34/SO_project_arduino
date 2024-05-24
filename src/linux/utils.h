#pragma once

#include <stdint.h>
#include <stdio.h>

#define MINUTES 60
#define HOURS 24
#define DAYS 30
#define MONTHS 12

// Struct to store the time averages
typedef struct {
    uint16_t minutes[MINUTES];
    uint16_t hourly[HOURS];
    uint16_t daily[DAYS];
    uint16_t monthly[MONTHS];
    uint16_t yearly;
} Data;

//read data from serial port
void serial_readData(int fd, Data* data);

//print data to stdout
void print_Data(Data* data);