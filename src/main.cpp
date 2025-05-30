#include <Arduino.h>
#include "Sonar.h"
#include "ServoControl.h"
#include "MotorControl.h"
#include "State.h"

#define CHECK_INTERVAL 200
#define DIST_THRESHOLD 20
#define CRITICAL_DISTANCE 10
#define TURN_INTERVAL 1000
#define BACKWARD_TIME 400

#define MAX_TURN_ANGLE 60
#define MIN_TURN_TIME 500
#define MAX_TURN_TIME 1500 


void mySetup() {
    Serial.begin(9600);
    initSonar();
    initEchoInterrupt();

    initServoControl();
    initMotorControl();
}

State_t currentState = IDLE;
uint32_t lastActionTime = 0;
uint16_t leftDistance = 0;
uint16_t rightDistance = 0;

uint32_t turnStartTime = 0;
uint32_t turnDuration = 0;

int bestAngle = 0;
int angleOffset = 0;
int absOffset = 0;


int main() {
    init();
    mySetup();


    while (true) {
        switch (currentState) {
            case IDLE:
                stopMotors();
                lookCenter();
                currentState = GO_FORWARD;
                lastActionTime = millis();
                break;

            case GO_FORWARD:
                forwardMotors();
                if (millis() - lastActionTime > CHECK_INTERVAL) {
                    uint16_t dist = measureDistance();
                    if (dist < CRITICAL_DISTANCE) {
                        stopMotors();
                        turnDuration = BACKWARD_TIME;
                        currentState = GO_BACKWARD;
                        lastActionTime = millis();
                    } else if (dist < DIST_THRESHOLD) {
                        currentState = OBSTACLE_DETECTED;
                        lastActionTime = millis();
                    }
                }

                break;

            case GO_BACKWARD:
                backwardMotors();
                if (millis() - lastActionTime > turnDuration) {
                    currentState = OBSTACLE_DETECTED;
                    lastActionTime = millis();
                }

                break;

            case OBSTACLE_DETECTED:
                stopMotors();
                currentState = SCAN_ALL;
                lastActionTime = millis();
                break;

            case SCAN_ALL:
                clearLookPoints();
                scanAllLookPoints();
                currentState = DECIDE_DIRECTION;
                lastActionTime = millis();
                break;

            case DECIDE_DIRECTION:
                bestAngle = getBestAngle();
                angleOffset = bestAngle - SERVO_CENTER_ANGLE;
                absOffset = abs(angleOffset);
                
                turnDuration = map(absOffset, 0, MAX_TURN_ANGLE, MIN_TURN_TIME, MAX_TURN_TIME);
                if (angleOffset < 0) {
                    currentState = TURN_LEFT;
                } else {
                    currentState = TURN_RIGHT;
                }

                break;

            case TURN_LEFT:
                if (turnStartTime == 0) {
                    leftTurnMotors();
                    turnStartTime = millis();
                } else if (millis() - turnStartTime >= turnDuration) {
                    stopMotors();
                    currentState = GO_FORWARD;
                    lastActionTime = millis();
                    turnStartTime = 0; // Reset turn timer
                    turnDuration = 0; // Reset turn duration
                }

                break;

            case TURN_RIGHT:
                if (turnStartTime == 0) {
                    rightTurnMotors();
                    turnStartTime = millis();
                } else if (millis() - turnStartTime >= turnDuration) {
                    stopMotors();
                    currentState = GO_FORWARD;
                    lastActionTime = millis();
                    turnStartTime = 0; // Reset turn timer
                    turnDuration = 0; // Reset turn duration
                }
        }
    }
}
