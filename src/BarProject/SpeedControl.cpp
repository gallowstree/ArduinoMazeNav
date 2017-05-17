#include "SpeedControl.h"
#include <Arduino.h>

SpeedControl::SpeedControl(volatile double* input, volatile double* output, double* setpoint, int pin) :
input(input),
output(output),
setpoint(setpoint),
pin(pin),
myPID(input, output, setpoint, kp, ki, kd, DIRECT) {
    myPID.SetSampleTime(50);
    //myPID.SetOutputLimits(60, 120);
}

void SpeedControl::enable() {
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void SpeedControl::disable() {
    myPID.SetMode(MANUAL);
}

void SpeedControl::updatePID() {
    
    myPID.Compute();
    analogWrite(pin, *output);

    if (pin != 2 ) return;
    Serial.print("pin: ");
    Serial.print(pin);
    Serial.print(" i:");
    Serial.print(*input);
    Serial.print(" o:");
    Serial.println(*output);
}