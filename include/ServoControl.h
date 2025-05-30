#ifndef __SERVO_CONTROL_H__
#define __SERVO_CONTROL_H__

#include <Servo.h>
#include <util/delay.h>
#include "Sonar.h"

#define SERVO_PIN 10
#define SERVO_CENTER_ANGLE 90
#define SERVO_MIN_ANGLE 30
#define SERVO_MAX_ANGLE 150
#define SERVO_STEP 30
#define SERVO_LOOK_POINTS ((SERVO_MAX_ANGLE - SERVO_MIN_ANGLE) / SERVO_STEP + 1)

#define SERVO_DELAY 300

typedef struct {
    int angle; // Angle in degrees
    uint16_t distance; // Distance in cm
} ServoLookPoint_t;

extern Servo servo;
extern int servoLookPointsCount;
extern ServoLookPoint_t servoLookPoints[SERVO_LOOK_POINTS];


void initServoControl(void);
void lookAtRightInstant(int angle);
void lookAtLeftInstant(int angle);
void lookCenter(void);
void initLookPoints(void);
void clearLookPoints(void);
void scanAllLookPoints(void);

int getBestAngle(void);


#endif // __SERVO_CONTROL_H__