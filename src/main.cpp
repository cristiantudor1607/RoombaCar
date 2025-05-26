#include <Arduino.h>
#include "MotorControl.h"
#include "Sonar.h"
#include "ServoControl.h"

extern AF_DCMotor motor1;
extern AF_DCMotor motor2;
extern AF_DCMotor motor3;
extern AF_DCMotor motor4;


int main(void) {
  Serial.begin(9600);
  Serial.println("Roomba Car Initializing...");

  initServoControl();
  
  initSonar();
  initTimer2();
  initEchoInterrupt();

  Serial.println("Initialization complete. Starting distance measurement...");

  while (1) {
    // uint16_t distance = measureDistance();
    // Serial.print("Distance: ");
    // Serial.print(distance);
    // Serial.println(" cm");
    // _delay_ms(100); // Delay for stability
    testServo(); // Test servo control
  }

}
