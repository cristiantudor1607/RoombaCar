#include <Arduino.h>
#include "Sonar.h"
#include "ServoControl.h"
#include "MotorControl.h"

void mySetup() {
    Serial.begin(9600);
    Serial.println("Booting...");

    initSonar();
    initEchoInterrupt();

    initServoControl();
    initMotorControl();

    Serial.println("Setup complete.");
}

int main() {
    init();

    mySetup();

    // forwardMotors(); // Asigură-te că roboțelul se mișcă înainte
    while (true) {
        servo.write(SERVO_CENTER_ANGLE); // Poziționează servo la centrul său
        // Așteaptă să se măsoare distanța
        uint16_t distance = measureDistance();
        Serial.print("Distanța măsurată: ");
        Serial.print(distance);
        Serial.println(" cm");


        // Pauză între cicluri
        Serial.println("---");
        delay(1000);
    }

    return 0;
}
