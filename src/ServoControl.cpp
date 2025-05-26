#include "ServoControl.h"


Servo servo;

void initServoControl(void) {
    servo.attach(SERVO_PIN);
    servo.write(90);
}

void lookAtRight(int angle) {
    servo.write(90 + angle);
    _delay_ms(500);
}

void lookAtLeft(int angle) {
    servo.write(90 - angle);
    _delay_ms(500);
}

