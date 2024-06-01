#include "timers.h"

// Timer1 setup
void setup_timer1(void) {

    // Set Timer to CTC (Clear Timer on Compare Match) mode
    TCCR1A = 0; 
    TCCR1B |= (1 << WGM12);

    // Set the Compare Match Register for 1 minute
    // Assuming a 16 MHz clock and a prescaler of 1024

    OCR1A = 65535; // Count to 65535, the maximum value of a 16-bit register!
    //we have to overflow and count to get a minute!

    OCR1A = 300; //DEBUG!!! TOGLIERE!!!!

    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Start Timer1 with prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    return;
}

// Timer 2 setup to toggle LED 13
void setup_timer2(void) {
    // Set Timer2 to CTC (Clear Timer on Compare Match) mode
    TCCR2A |= (1 << WGM21);
    TCCR2B = 0;

    // Set Compare Match Register for a desired interval
    OCR2A = 0xFF;  // Assuming a 16 MHz clock and prescaler of 1024, this gives approximately 1 Hz

    // Enable Timer2 compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    // Start Timer2 with prescaler 1024
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
}

