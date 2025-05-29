#include "MotorControl.h"

AF_DCMotor leftMotors(1);
AF_DCMotor rightMotors(2);
uint8_t motorSpeed = 255;


void initMotorControl(void) {
    leftMotors.setSpeed(motorSpeed);
    rightMotors.setSpeed(motorSpeed);

    leftMotors.run(RELEASE);
    rightMotors.run(RELEASE);
}

void stopMotors(void) {
    leftMotors.run(RELEASE);
    rightMotors.run(RELEASE);
}
void forwardMotors(void) {
    leftMotors.setSpeed(motorSpeed);
    rightMotors.setSpeed(motorSpeed);
    leftMotors.run(FORWARD);
    rightMotors.run(FORWARD);
}

void backwardMotors(void) {
    leftMotors.setSpeed(motorSpeed);
    rightMotors.setSpeed(motorSpeed);
    leftMotors.run(BACKWARD);
    rightMotors.run(BACKWARD);
}

void leftTurnMotors(void) {
    leftMotors.setSpeed(motorSpeed);
    rightMotors.setSpeed(motorSpeed);
    leftMotors.run(BACKWARD);
    rightMotors.run(FORWARD);
}

void rightTurnMotors(void) {
    leftMotors.setSpeed(motorSpeed);
    rightMotors.setSpeed(motorSpeed);
    leftMotors.run(FORWARD);
    rightMotors.run(BACKWARD);
}

void setMotorSpeed(uint8_t speed) {
    motorSpeed = speed;
}