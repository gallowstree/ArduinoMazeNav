#include "MotionController.h"

MotionController::MotionController(Odometer* odometer, ImuReader* imu, MotorDriver* motors, SpeedControl* rightSpeedCtl, SpeedControl* leftSpeedCtl) : 
imu(imu),
motors(motors), 
odometer(odometer),
rightSpeedCtl(rightSpeedCtl),
leftSpeedCtl(leftSpeedCtl){}

void MotionController::rotate(float degrees, bool clockwise) {
   
}

void MotionController::stop() {
    motors->stop();
}

void MotionController::moveForward(float cm) {        
    waitForDistance(cm, true);    
}

void MotionController::moveBackwards(float cm) {    
    waitForDistance(cm, false);    
}

void MotionController::waitForDistance(float cm, bool forward) {

    odometer->enable();
    rightSpeedCtl->enable();
    leftSpeedCtl->enable();

    if (forward) 
        motors->moveForward(); 
    else 
        motors->moveBackwards();
    
    float r = 0, l = 0;
    while ((r = odometer->getRightDistance()) < cm ||
           (l = odometer->getLeftDistance()) < cm) {
        rightSpeedCtl->updatePID();
        leftSpeedCtl->updatePID();
        if (r >= cm) motors->stopRight();
        if (l >= cm) motors->stopLeft();
    }

    motors->stop();
    rightSpeedCtl->disable();
    leftSpeedCtl->disable();
    odometer->disable();
}