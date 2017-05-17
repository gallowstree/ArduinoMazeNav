#ifndef MYARDUINOPROJECT_PID_H
#define MYARDUINOPROJECT_PID_H

#include "PID_v1.h"
class SpeedControl {
public:
    SpeedControl(volatile double* input, volatile double* output, double* setpoint, int pin);
    void enable();
    void disable();
    void updatePID();

private:
    PID myPID;
    // double kp = 0.5;
    // double ki = 0.0008;
    // double kd = 0.0005;

    double kp = 100.0;
    double ki = 1.0;
    double kd = 0.0;

    volatile double* input;
    volatile double* output;
    double* setpoint;
    int pin;
};

#endif