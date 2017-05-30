#ifndef MYARDUINOPROJECT_MOTIONCONTROLLER_H
#define MYARDUINOPROJECT_MOTIONCONTROLLER_H

#include "MotorDriver.h"
#include "Odometer.h"
#include "Motion.h"

class MotionController {
public:
    MotionController(Odometer* odometer, MotorDriver * motors);
    void rotate(float degrees, bool clockwise);    
    void stop();
    void moveForward(float cm);
	void moveBackwards(float cm);	

    int rightPulseLength = 140;
    int leftPulseLength = 200;
private:    
    MotorDriver* motors;
    Odometer* odometer;
    void waitForDistance(float cm, Motion m);  
    
};

#endif