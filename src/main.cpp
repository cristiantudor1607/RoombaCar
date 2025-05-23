#include <Arduino.h>
#include "MotorControl.h"
#include "Sonar.h"
#include "RoombaCarInterrupts.h"

extern AF_DCMotor motor1;
extern AF_DCMotor motor2;
extern AF_DCMotor motor3;
extern AF_DCMotor motor4;

void setup() {
  initTimer1(); // Initialize Timer1 for obstacle detection
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
