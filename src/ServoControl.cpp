#include "ServoControl.h"

Servo servo;
ServoLookPoint_t servoLookPoints[SERVO_LOOK_POINTS];
int servoLookPointsCount = 0;

void initLookPoints(void) {
    for (int i = SERVO_MIN_ANGLE; i <= SERVO_MAX_ANGLE; i += SERVO_STEP) {
        servoLookPoints[servoLookPointsCount].angle = i;
        servoLookPoints[servoLookPointsCount].distance = INT16_MIN;
        servoLookPointsCount++;
    }
}

void clearLookPoints(void) {
    for (int i = 0; i < servoLookPointsCount; i++)
        servoLookPoints[i].distance = INT16_MIN; // Reset distances to max
}

void scanAllLookPoints(void) {
    for (int i = 0; i < servoLookPointsCount; i++) {
        servo.write(servoLookPoints[i].angle);
        delay(SERVO_DELAY); // Allow time for servo to move
        uint16_t distance = measureDistance(); // Measure distance at this angle
        servoLookPoints[i].distance = distance; // Store the measured distance
    }

    lookCenter(); // Center the servo after scanning
}

int getBestAngle(void) {
    int bestIndex = 0;
    uint32_t maxDistance = servoLookPoints[0].distance;

    for (int i = 1; i < servoLookPointsCount; i++) {
        if (servoLookPoints[i].distance > maxDistance) {
            maxDistance = servoLookPoints[i].distance;
            bestIndex = i;
        }
    }

    return servoLookPoints[bestIndex].angle;
}

void initServoControl(void) {
    initLookPoints(); // Initialize look points

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

