#ifndef __SERVO_CONTROL_H__
#define __SERVO_CONTROL_H__

#include <Servo.h>
#include <util/delay.h>

#define SERVO_PIN 10

extern Servo servo;

void initServoControl(void);
void lookAtRight(int angle);
void lookAtLeft(int angle);


#endif // __SERVO_CONTROL_H__