#include "timers.h"

// Timer1 setup
void setup_timer1(void) {

    // Set Timer to CTC (Clear Timer on Compare Match) mode
    TCCR1A = 0; 
    TCCR1B |= (1 << WGM12);

    // Set the Compare Match Register for 1 second
    // Assuming a 16 MHz clock and a prescaler of 1024
    OCR1A = 15624;

    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Start Timer1 with prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10); // CS12 = 1, CS10 = 1 => Prescaler = 1024

    return;
}


// Timer 2 setup to sample current sensor at 200 Hz
void setup_timer2(void) {
    // Set Timer2 to CTC (Clear Timer on Compare Match) mode
    TCCR2A |= (1 << WGM21);
    TCCR2B = 0;

    // Set Compare Match Register for 200 Hz
    OCR2A = 124;  // Assuming a 16 MHz clock and prescaler of 64, this gives 200 Hz

    // Enable Timer2 compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    // Start Timer2 with prescaler 64
    TCCR2B |= (1 << CS22); // CS22 = 1, CS21 = 0, CS20 = 0 => Prescaler = 64
}

