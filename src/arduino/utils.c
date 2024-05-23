#include "./utils.h"

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
uint8_t process_time(uint8_t *minutes, uint8_t *hours, uint8_t *days, uint8_t *months, uint8_t *years){
  //process time here...

  uint8_t retval = 0;

  //when we reach the end of the hour, we reset the minutes and increment the hour
  if(*minutes > MINUTES -1){
    *minutes = 0;
    *hours += 1;

    retval = 1;
  }

   //when we reach the end of the day, we reset the hours and increment the day
  if(*hours > HOURS -1){
    *hours = 0;
    *days += 1;
  }


  //when we reach the end of the month, we reset the days and increment the month
  if(*days > DAYS -1){
    *days = 0;
    *months += 1;
  }

  //when we reach the end of the year, we reset the months and increment the year
  if(*months > MONTHS -1){
    *months = 0;
    *years += 1;
  }


  return retval;
}