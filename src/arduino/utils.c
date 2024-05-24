#include "utils.h"

//enable interrupts
void enable_interrupts(void){
  sei();
}

//disable interrupts
void disable_interrupts(void){
  cli();
}

//others useful things here...

//process time
uint8_t process_time(Data *data, Time *time, uint16_t adc_value){
  //process time here...

  //return 1 if we have reached the end of the hour
  uint8_t retval = 0;

  //we store the minutes data
  data->minutes[time->minutes] = adc_value;

  //when we reach the end of the hour, we reset the minutes and increment the hour
  if(time->minutes > MINUTES -1){
    time->minutes = 0;

    //we store the hourly data which is the average of the minutes
    uint16_t sum = 0;
    for(uint8_t i = 0; i < MINUTES; i++){
      sum += data->minutes[i];
    }
    data->hourly[time->hours] = sum / MINUTES;

    time->hours += 1;
    retval = 1;
  }

  //when we reach the end of the day, we reset the hours and increment the day
  if(time->hours > HOURS -1){
    time->hours = 0;

    //we store the daily data which is the average of the hours
    uint16_t sum = 0;
    for(uint8_t i = 0; i < HOURS; i++){
      sum += data->hourly[i];
    }
    data->daily[time->days] = sum / HOURS;

    time->days += 1;
  }

  //when we reach the end of the month, we reset the days and increment the month
  if(time->days > DAYS -1){
    time->days = 0;

    //we store the monthly data which is the average of the days
    uint16_t sum = 0;
    for(uint8_t i = 0; i < DAYS; i++){
      sum += data->daily[i];
    }
    data->monthly[time->months] = sum / DAYS;

    time->months += 1;
  }

  //when we reach the end of the year, we reset the months and increment the year
  if(time->months > MONTHS -1){
    time->months = 0;

    //we store the yearly data which is the average of the months
    uint16_t sum = 0;
    for(uint8_t i = 0; i < MONTHS; i++){
      sum += data->monthly[i];
    }
    data->yearly = sum / MONTHS;

    time->years += 1;
  }

  return retval;
}