#ifndef __MOTOR_CONTROL_H__
#define __MOTOR_CONTROL_H__

#include <AFMotor.h>

extern AF_DCMotor motor1;
extern AF_DCMotor motor2;
extern AF_DCMotor motor3;
extern AF_DCMotor motor4;

void stopMotors();
void forwardMotors();
void backwardMotors();
void turnLeftMotors();
void turnRightMotors();


#endif // __MOTOR_CONTROL_H__