#ifndef __SERVO_CONTROL_H__
#define __SERVO_CONTROL_H__

#include <Servo.h>
#include <util/delay.h>

#define SERVO_PIN 10
#define SERVO_CENTER_ANGLE 90
#define SERVO_MIN_ANGLE 45
#define SERVO_MAX_ANGLE 135
#define SERVO_STEP 15
#define SERVO_LOOK_POINTS ((SERVO_MAX_ANGLE - SERVO_MIN_ANGLE) / SERVO_STEP + 1)

extern Servo servo;
extern int servoLookPointsCount;
extern int servoLookAngles[SERVO_LOOK_POINTS];
extern int servoDistances[SERVO_LOOK_POINTS];

void initServoControl(void);
void lookAtRightInstant(int angle);
void lookAtLeftInstant(int angle);
void lookCenter(void);


#endif // __SERVO_CONTROL_H__