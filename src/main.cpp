#include <Arduino.h>
#include "MotorControl.h"
#include "Sonar.h"
#include "RoombaCarInterrupts.h"

extern AF_DCMotor motor1;
extern AF_DCMotor motor2;
extern AF_DCMotor motor3;
extern AF_DCMotor motor4;

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Roomba Car Initializing...");
//   // Initialize sonar
//   initSonar();
//   initTimer0();
//   initEchoInterrupt();
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   uint16_t distance = measureDistance();
//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");
// }

int main(void) {
  Serial.begin(9600);
  Serial.println("Roomba Car Initializing...");
  
  initSonar();
  initTimer2();
  initEchoInterrupt();

  while (1) {
    uint16_t distance = measureDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    _delay_ms(100); // Delay for stability
  }

}
