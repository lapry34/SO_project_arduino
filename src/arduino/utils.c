#include "utils.h"

//others useful things here...

//process time
void process_time(Data *data, Time *time, uint16_t adc_value){
  //process time here...

  //we store the seconds data
  data->seconds[time->seconds] = adc_value;

  time->seconds += 1;

  //when we reach the end of the minute, we reset the seconds and increment the minute
  if(time->seconds > SECONDS -1){
    time->seconds = 0;

    //we store the minute data which is the average of the seconds
    uint16_t sum = 0;
    for(uint8_t i = 0; i < SECONDS; i++){
      sum += data->seconds[i];
    }
    data->minutes[time->minutes] = sum / SECONDS;

    time->minutes += 1;
  }

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

  return;
}