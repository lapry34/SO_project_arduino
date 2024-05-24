#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MINUTES 60
#define HOURS 24
#define DAYS 30
#define MONTHS 12

// Error handling
#define handle_error(msg) \
do { perror(msg); exit(EXIT_FAILURE); } while (0)


// Struct to store the time averages
typedef struct {
    uint16_t minutes[MINUTES];
    uint16_t hourly[HOURS];
    uint16_t daily[DAYS];
    uint16_t monthly[MONTHS];
    uint16_t yearly;
} __attribute__((packed)) Data;

//read data from serial port
void serial_readData(int fd, Data* data);

//print data to stdout
void print_Data(Data* data);