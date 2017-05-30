#include "Motion.h"


Motion::Motion(MotorDriver* mtr, int direction, int leftPwm, int rightPwm) : 
mtr(mtr), 
direction(direction), 
leftPwm(leftPwm), 
rightPwm(rightPwm) { }

void Motion::right() {
    mtr->setRightPulseLength(rightPwm);

    if (direction == forward || direction == counterclockwise)
        mtr->rightForward();
    else if (direction == backwards || direction == clockwise)
        mtr->rightBackwards();
}

void Motion::left() {
    mtr->setLeftPulseLength(leftPwm);

    if (direction == forward || direction == clockwise)
        mtr->leftForward();
    else if (direction == backwards || direction == counterclockwise)
        mtr->leftBackwards();
}

int Motion::getLeftPwm() {
    return leftPwm;
}

int Motion::getRightPwm() {
    return rightPwm;
}