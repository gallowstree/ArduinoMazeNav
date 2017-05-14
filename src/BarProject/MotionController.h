#ifndef MYARDUINOPROJECT_MOTIONCONTROLLER_H
#define MYARDUINOPROJECT_MOTIONCONTROLLER_H

#include "ImuReader.h"
#include "MotorDriver.h"
#include "Odometer.h"

class MotionController {
public:
    MotionController(Odometer* odometer, ImuReader * imu, MotorDriver * motors);
    void rotate(float degrees, bool clockwise);    
    void stop();
    void moveForward(float cm);
	void moveBackwards(float cm);	
private:
    ImuReader* imu;
    MotorDriver* motors;
    Odometer* odometer;

    void waitForDistance(float cm);

};

#endif