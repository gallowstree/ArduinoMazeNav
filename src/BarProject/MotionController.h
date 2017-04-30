#ifndef MYARDUINOPROJECT_MOTIONCONTROLLER_H
#define MYARDUINOPROJECT_MOTIONCONTROLLER_H

#include "ImuReader.h"
#include "MotorDriver.h"

class MotionController {
public:
    MotionController(ImuReader * imu, MotorDriver * motors);
    void rotate(int degrees, bool clockwise);
private:
    ImuReader* imu;
    MotorDriver* motors;

};

#endif