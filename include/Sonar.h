#ifndef __SONAR__H__
#define __SONAR__H__

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define TRIG_DDR DDRC
#define TRIG_PORT PORTC
#define TRIG_PIN PC0

#define ECHO_DDR DDRC
#define ECHO_PORT PORTC
#define ECHO_PIN PC1

void initSonar(void);
void sendTriggerPulse(void);

void checkObstacle(void);


#endif // __SONAR__H__