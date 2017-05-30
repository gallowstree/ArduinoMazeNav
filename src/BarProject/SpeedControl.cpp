#include "SpeedControl.h"
#include <Arduino.h>

SpeedControl::SpeedControl(volatile double* input, volatile double* output, double* setpoint, int pin) :
input(input),
output(output),
setpoint(setpoint),
pin(pin),
myPID(input, output, setpoint, kp, ki, kd, DIRECT) {
    myPID.SetSampleTime(50);
     myPID.SetOutputLimits(120, 255);
}

void SpeedControl::enable() {
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void SpeedControl::disable() {
    myPID.SetMode(MANUAL);
    *output = 0;
}

void SpeedControl::updatePID() {
    myPID.Compute();

    // Serial.print("Pin: ");
    // Serial.print(pin);
    // Serial.print(" Output: ");
    // Serial.println(*output);
    analogWrite(pin, *output);
}

