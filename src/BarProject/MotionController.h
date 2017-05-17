#ifndef MYARDUINOPROJECT_MOTIONCONTROLLER_H
#define MYARDUINOPROJECT_MOTIONCONTROLLER_H

#include "ImuReader.h"
#include "MotorDriver.h"
#include "Odometer.h"
#include "SpeedControl.h"

class MotionController {
public:
    MotionController(Odometer* odometer, ImuReader * imu, MotorDriver * motors, SpeedControl* rightSpeedCtl, SpeedControl* leftSpeedCtl);
    void rotate(float degrees, bool clockwise);    
    void stop();
    void moveForward(float cm);
	void moveBackwards(float cm);	
private:
    ImuReader* imu;
    MotorDriver* motors;
    Odometer* odometer;
    SpeedControl* rightSpeedCtl;
    SpeedControl* leftSpeedCtl;

    void waitForDistance(float cm, bool forward);

};

#endif