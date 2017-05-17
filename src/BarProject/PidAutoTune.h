#ifndef MYARDUINOPROJECT_PID_AUTOTUNE_H
#define MYARDUINOPROJECT_PID_AUTOTUNE_H

#include "PID_v1.h"
#include "PID_AutoTune_v0.h"
#include <Arduino.h>
/*
class PidAutoTune {
public:
    PidAutoTune(double* input, double* output, double setpoint, int port);
    void tune();

private:
    void changeAutoTune(boolean stop);
    void print(boolean tuning);

    PID myPID;
    PID_ATune aTune;
    int port;

    byte ATuneModeRemember;
    double* input;
    double* output;
    double setpoint;
    double kp = 2, ki = 0.5, kd = 2;

    double aTuneStep = 50, aTuneNoise = 1, aTuneStartValue = 0;
    unsigned int aTuneLookBack = 20;
};
*/
#endif