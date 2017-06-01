#ifndef MYARDUINOPROJECT_PID_H
#define MYARDUINOPROJECT_PID_H

#include "PID_v1.h"
#include "MotorDriver.h"
class SpeedControl {
public:
    SpeedControl(volatile double* leftSpeed, volatile double* rightSpeed, MotorDriver* motors);
    void enable();
    void disable();
    void updatePID();

private:
    PID myPID;
    // double kp = 1.5;
    // double ki = 0.5;
    // double kd = 1;

    // ahora sí
    // double kp = 1.5;
    // double ki = 50;
    // double kd = 2.5;

    double kp = 1;
    double ki = 50;
    double kd = 2.5;

    bool enabled = false;

    double minPwm = 100;
    double maxPwm = 255;

    volatile double* leftSpeed; 
    volatile double* rightSpeed;

    volatile double input = 0;
    volatile double output = 0;
    double setpoint = 0;    
    MotorDriver* motors;
};

#endif