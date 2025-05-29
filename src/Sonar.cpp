#include "Sonar.h"

volatile uint32_t timerTicks = 0;
volatile uint32_t echoStartTime = 0;
volatile uint32_t echoEndTime = 0;
volatile uint8_t measuring = 0;
volatile uint8_t echoDone = 0;


void initSonar(void) {
    // Set TRIG_PIN as output
    TRIG_DDR |= (1 << TRIG_PIN);
    // Initialize TRIG_PIN to LOW
    TRIG_PORT &= ~(1 << TRIG_PIN);

    // Set ECHO_PIN as input
    ECHO_DDR &= ~(1 << ECHO_PIN);

}

void initEchoInterrupt(void) {
    // Enable external interrupt on INT0 (ECHO_PIN)
    // Trigger on any logical change
    EICRA |= (1 << ISC00);
    EICRA &= ~(1 << ISC01);
    
    // Clear any pending interrupts on INT0
    EIFR |= (1 << INTF0);

    // Enable INT0 interrupt
    EIMSK |= (1 << INT0);
}


ISR(INT0_vect) {
    // This interrupt is triggered on the rising edge of the ECHO_PIN
    if (ECHO_PIN_REGISTER & (1 << ECHO_PIN)) {
        // Rising edge detected, record the start time
        // echoStartTime = timerTicks * 256UL + TCNT2;
        echoStartTime = micros(); // Use micros() for more precise timing

        // Set measuring flag to indicate we are measuring
        measuring = 1; 

        // Clear echo done flag
        echoDone = 0;
    } else {
        if (measuring) {
            // Falling edge detected, record the end time
            // echoEndTime = timerTicks * 256UL + TCNT2;
            echoEndTime = micros(); // Use micros() for more precise timing

            // Clear measuring flag
            measuring = 0;

            // Set echo done flag to indicate measurement is complete
            echoDone = 1;
        }
    }
}


void sendTriggerPulse(void) {
    // Send a 10 microsecond pulse to TRIG_PIN
    TRIG_PORT |= (1 << TRIG_PIN); // Set TRIG_PIN HIGH
    _delay_us(10); // Wait for 10 microseconds
    TRIG_PORT &= ~(1 << TRIG_PIN); // Set TRIG_PIN LOW
}

uint16_t measureDistance(void) {
    echoDone = 0;
    measuring = 0;
    sendTriggerPulse();

    while (!echoDone) {
        // așteaptă ISR să seteze echoDone
    }

    uint32_t durationUs;
    if (echoEndTime >= echoStartTime) {
        durationUs = echoEndTime - echoStartTime;
    } else {
        // micros() a dat overflow
        durationUs = (0xFFFFFFFF - echoStartTime) + echoEndTime + 1;
    }

    uint16_t distanceCm = durationUs / 58;

    return distanceCm;
}

