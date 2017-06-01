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
    double kp = 0.4;
    double ki = 0.2;
    double kd = 1;
    bool enabled = false;

    double minPwm = 100;
    double maxPwm = 255;
/*
    double kp = 100.0;
    double ki = 1.0;
    double kd = 0.0;
*/
    // double kp = 30.0;
    // double ki = 0.05;
    // double kd = 1.0;

    volatile double* leftSpeed; 
    volatile double* rightSpeed;

    volatile double input = 0;
    volatile double output = 0;
    double setpoint = 0;    
    MotorDriver* motors;
};

#endif