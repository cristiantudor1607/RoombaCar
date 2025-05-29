#ifndef __MOTOR_CONTROL_H__
#define __MOTOR_CONTROL_H__

#include <AFMotor.h>

extern AF_DCMotor leftMotors;
extern AF_DCMotor rightMotors;
extern uint8_t motorSpeed; // Default speed

void initMotorControl(void);
void stopMotors(void);
void forwardMotors(void);
void backwardMotors(void);
void leftTurnMotors(void);
void rightTurnMotors(void);

void setMotorSpeed(uint8_t speed);

#endif // __MOTOR_CONTROL_H__