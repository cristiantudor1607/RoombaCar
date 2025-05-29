#ifndef __SONAR__H__
#define __SONAR__H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <Arduino.h>

#define TRIG_DDR DDRB
#define TRIG_PORT PORTB
#define TRIG_PIN PB5 // Using PB5 for TRIG_PIN, which is D13 on ATmega328P

#define ECHO_DDR DDRD
#define ECHO_PORT PORTD
#define ECHO_PIN_REGISTER PIND
#define ECHO_PIN PD2 // Using PD2 for ECHO_PIN, which is INT0 on ATmega328P

void initSonar(void);
void initTimer2(void);
void initEchoInterrupt(void);

uint32_t getMilis(void);

uint16_t measureDistance(void);
void sendTriggerPulse(void);

#endif // __SONAR__H__