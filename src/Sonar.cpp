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

void initTimer2(void) {
    // Set Timer0 to generate interrupt on overflow
    TCCR2A = 0; // Normal mode

    // Clear Timer/Counter Control Register B
    TCCR2B = 0; 

    // Clear Timer/Counter Register
    TCNT2 = 0;

    // Prescaler set to 64
    TCCR2B |= (1 << CS22); // 16MHz / 64 = 250kHz, each tick = 4us

    // Enable Timer0 overflow interrupt
    TIMSK2 |= (1 << TOIE2);
    
    // Enable global interrupts
    sei();
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

ISR(TIMER2_OVF_vect) {
    // Increment timer ticks on Timer0 overflow
    timerTicks++; // Each overflow = 256 ticks = 256  *  4 us = 1024 us = 1.024 ms
}

ISR(INT0_vect) {
    // This interrupt is triggered on the rising edge of the ECHO_PIN
    if (ECHO_PIN_REGISTER & (1 << ECHO_PIN)) {
        // Rising edge detected, record the start time
        echoStartTime = timerTicks * 256UL + TCNT2;

        // Set measuring flag to indicate we are measuring
        measuring = 1; 

        // Clear echo done flag
        echoDone = 0;
    } else {
        if (measuring) {
            // Falling edge detected, record the end time
            echoEndTime = timerTicks * 256UL + TCNT2;

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
    // Disable interrupts to ensure atomic operation
    cli();
    echoDone = 0; // Reset echo done flag
    measuring = 0; // Reset measuring flag
    timerTicks = 0; // Reset timer ticks
    TCNT2 = 0; // Reset Timer0 counter
    sei(); // Re-enable interrupts

    sendTriggerPulse(); // Send the trigger pulse
    while (!echoDone) {
        // Wait for the echo measurement to complete
    }

    // Calculate the duration of the echo pulse
    uint32_t durationTicks = echoEndTime - echoStartTime;
    // Serial.print("Duration Ticks: ");
    // Serial.println(durationTicks);

    // Convert timer ticks to microseconds (1 tick = 4 us)
    uint32_t durationUs = durationTicks * 4;
    // Serial.print("Duration (us): ");
    // Serial.println(durationUs);

    // Calculate distance in cm (speed of sound is approximately 343 m/s or 0.0343 cm/us)
    // uint16_t distanceCm = (durationUs * 0.0343) / 2; // Divide by 2 for round trip
    uint16_t distanceCm = durationUs / 58;

    return distanceCm; // Return the measured distance in cm
}

void checkObstacle(void) {

}
