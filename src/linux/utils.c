#include "utils.h"


void serial_readData(int fd, Data* data) {
    // Read the data from the serial port
    
    int nchars = read(fd, data, sizeof(Data));

    if (nchars < 0) handle_error("read");

    return;
}


void print_Data(Data* data) {
    // Print the data in the Data struct
    
    printf("Minutes: ");
    for (int i = 0; i < MINUTES; i++) {
        printf("%d ", data->minutes[i]);
    }
    printf("\n");

    printf("Hourly: ");
    for (int i = 0; i < HOURS; i++) {
        printf("%d ", data->hourly[i]);
    }
    printf("\n");

    printf("Daily: ");
    for (int i = 0; i < DAYS; i++) {
        printf("%d ", data->daily[i]);
    }
    printf("\n");

    printf("Monthly: ");
    for (int i = 0; i < MONTHS; i++) {
        printf("%d ", data->monthly[i]);
    }
    printf("\n");

    printf("Yearly: %d\n", data->yearly);

    return;
}