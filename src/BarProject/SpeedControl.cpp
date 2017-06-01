#include "SpeedControl.h"
#include <Arduino.h>

SpeedControl::SpeedControl(volatile double* leftSpeed, volatile double* rightSpeed, MotorDriver* motors) :
leftSpeed(leftSpeed),
rightSpeed(rightSpeed),
motors(motors),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT) {
    myPID.SetSampleTime(50);
    myPID.SetOutputLimits(-15, 15);
}

void SpeedControl::enable() {
    enabled = true;
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void SpeedControl::disable() {
    myPID.SetMode(MANUAL);
    enabled = false;
}

void SpeedControl::updatePID() {
    if (!enabled)
        return;

    auto diff = *leftSpeed - *rightSpeed;
    input = diff;//abs(diff);
    if (!myPID.Compute()) return;

    output = abs(output);

    auto newLeft  =  motors->leftPulseLength  + ( diff > 0 ? -(output) : output );
    auto newRight =  motors->rightPulseLength + ( diff > 0 ? output : -(output) );

    if (newLeft > maxPwm) newLeft = maxPwm;
    else if (newLeft < minPwm) newLeft = minPwm;

    if (newRight > maxPwm) newRight = maxPwm;
    else if (newRight < minPwm) newRight = minPwm;
    // Serial.print("i: ");
    // Serial.print(input);
    // Serial.print("o: ");
    // Serial.print(output);
    // Serial.print(" lv: ");
    // Serial.print(*leftSpeed);
    // Serial.print(" rv: ");
    // Serial.print(*rightSpeed);
    // Serial.print(" nl: ");
    // Serial.print(newLeft);
    // Serial.print(" nr: ");
    // Serial.println(newRight);

    motors->setLeftPulseLength(newLeft);
    motors->setRightPulseLength(newRight);
}

