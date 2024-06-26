#include "utils.h"


void serial_readData(int fd, Data* data) {
    // Read the data from the serial port

    assert(data != NULL && "data ptr is NULL");
    assert(fd >= 0 && "fd is negative");
    
    int nchars = read(fd, data, sizeof(Data));

    if (nchars < 0) handle_error("read");

    return;
}


void print_Data(Data* data) {
    // Print the data in the Data struct

    assert(data != NULL && "data ptr is NULL");
    
    printf("Seconds: ");
    for (int i = 0; i < SECONDS; i++) {
        printf("%f ", predict_mA(data->seconds[i]));
    }

    printf("\n");

    printf("Minutes: ");
    for (int i = 0; i < MINUTES; i++) {
        printf("%f ", predict_mA(data->minutes[i]));
    }
    printf("\n");

    printf("Hourly: ");
    for (int i = 0; i < HOURS; i++) {
        printf("%f ", predict_mA(data->hourly[i]));
    }
    printf("\n");

    printf("Daily: ");
    for (int i = 0; i < DAYS; i++) {
        printf("%f ", predict_mA(data->daily[i]));
    }
    printf("\n");

    printf("Monthly: ");
    for (int i = 0; i < MONTHS; i++) {
        printf("%f ", predict_mA(data->monthly[i]));
    }
    printf("\n");

    printf("Yearly: %f ", predict_mA(data->yearly));

    return;
}

void dump_Data(Data* data, const char* filename) {
    // Dump the data in the Data struct to a file
    int ret;

    assert(data != NULL && "data ptr is NULL");
    assert(filename != NULL && "filename is NULL");

    FILE* file = fopen(filename, "w");
    if (file == NULL) handle_error("fopen");
    
    for (int i = 0; i < SECONDS; i++) {
        float current_mA = predict_mA(data->seconds[i]);
        ret = fprintf(file, "%d %3.4f\n", i, current_mA); //fprintf controls EINTR error internally
        if (ret < 0) handle_error("fprintf");
    }

    ret = fclose(file);
    if (ret < 0) handle_error("fclose");
}

//advanced machine learning model to predict current in mA
float predict_mA(uint16_t value) {
  float current_mA = (float)value * SLOPE + INTERCEPT;
  return current_mA < 0 ? 0 : current_mA;
}
