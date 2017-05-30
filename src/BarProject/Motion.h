
#ifndef MYARDUINOPROJECT_MOTION_H
#define MYARDUINOPROJECT_MOTION_H

#include "MotorDriver.h"


class Motion {
public:
    Motion(MotorDriver* mtr, int direction, int leftPwm, int rightPwm);
    void right();
    void left();
    int getLeftPwm();
    int getRightPwm();

    static const int forward = 0;
    static const int backwards = 1;
    static const int clockwise = 2;
    static const int counterclockwise = 3;
private:
    int direction;
    int leftPwm;
    int rightPwm;
    MotorDriver* mtr;
};

#endif