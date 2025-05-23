#include "Sonar.h"

void initSonar(void) {
    // Set TRIG_PIN as output
    TRIG_DDR |= (1 << TRIG_PIN);
    // Set ECHO_PIN as input
    ECHO_DDR &= ~(1 << ECHO_PIN);

    // Initialize TRIG_PIN to LOW
    TRIG_PORT &= ~(1 << TRIG_PIN);
}

void sendTriggerPulse(void) {
    // Send a 10 microsecond pulse to TRIG_PIN
    TRIG_PORT |= (1 << TRIG_PIN); // Set TRIG_PIN HIGH
    _delay_us(10); // Wait for 10 microseconds
    TRIG_PORT &= ~(1 << TRIG_PIN); // Set TRIG_PIN LOW
}