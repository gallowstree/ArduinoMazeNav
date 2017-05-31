#include "SpeedControl.h"
#include <Arduino.h>

SpeedControl::SpeedControl(volatile double* leftSpeed, volatile double* rightSpeed, MotorDriver* motors) :
leftSpeed(leftSpeed),
rightSpeed(rightSpeed),
motors(motors),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT) {
    myPID.SetSampleTime(25);
    myPID.SetOutputLimits(0, 10);
}

void SpeedControl::enable() {
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void SpeedControl::disable() {
    myPID.SetMode(MANUAL);
    output = 0;
}

void SpeedControl::updatePID() {
    auto diff = *leftSpeed - *rightSpeed;
    input = abs(diff);
    myPID.Compute();

    auto newLeft  =  motors->leftPulseLength  + ( diff > 0 ? -(output) : output );
    auto newRight =  motors->rightPulseLength + ( diff > 0 ? output : -(output) );

    Serial.print("output: ");
    Serial.print(output);
    Serial.print(" lv: ");
    Serial.print(*leftSpeed);
    Serial.print(" rv: ");
    Serial.print(*rightSpeed);
    Serial.print(" nl: ");
    Serial.print(newLeft);
    Serial.print(" nr: ");
    Serial.println(newRight);

    motors->setLeftPulseLength(newLeft);
    motors->setRightPulseLength(newRight);
}

