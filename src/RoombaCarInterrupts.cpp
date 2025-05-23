#include "RoombaCarInterrupts.h"

void initTimer1(void) {
    cli(); // Disable interrupts

    // Clear TCCR1A and TCCR1B registers
    TCCR1A = 0;
    TCCR1B = 0;

    // Set Timer1 to CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Set the compare value to 100ms (assuming 16MHz clock and prescaler of 1024)
    OCR1A = 156; // (16MHz / 1024) * 0.1s - 1

    // Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Enable Timer1 compare interrupt on OCR1A match
    TIMSK1 |= (1 << OCIE1A);

    // Enable global interrupts
    sei();
}

ISR(TIMER1_COMPA_vect) {
    // This interrupt will be called every 100ms
    // Call the function to check for obstacles
    checkObstacle();
}