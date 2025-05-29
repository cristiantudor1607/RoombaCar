#include "ServoControl.h"

Servo servo;
int servoLookPointsCount;
int servoLookAngles[SERVO_LOOK_POINTS];
int servoDistances[SERVO_LOOK_POINTS];

static void initServoLookPoints(void) {
    servoLookPointsCount = 0;
    for (int angle = SERVO_MIN_ANGLE; angle <= SERVO_MAX_ANGLE; angle += SERVO_STEP) {
        servoLookAngles[servoLookPointsCount] = angle;
        servoDistances[servoLookPointsCount] = INT32_MAX;
        servoLookPointsCount++;
    }
}

void initServoControl(void) {
    initServoLookPoints();
    
    servo.attach(SERVO_PIN);
    servo.write(SERVO_CENTER_ANGLE);
}

void lookAtRightInstant(int angle) {
    servo.write(90 + angle);
}

void lookAtLeftInstant(int angle) {
    servo.write(90 - angle);
}

void lookCenter(void) {
    servo.write(SERVO_CENTER_ANGLE);
}

