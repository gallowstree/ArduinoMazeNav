#include "MotionController.h"
#include <math.h>

MotionController::MotionController(Odometer* odometer, MotorDriver* motors, SpeedControl* speedCtl) : 
motors(motors), 
odometer(odometer),
speedCtl(speedCtl){

}

void MotionController::rotate(float degrees, bool clockwise) {
    // float rads = degrees * TWO_PI / 360;
    // float rotationRadius = 7.8;
    // float targetDistance = rads * rotationRadius;
    //waitForDistance(targetDistance,  Motion(motors, clockwise ? Motion::clockwise : Motion::counterclockwise, leftPulseLength, rightPulseLength));
}

void MotionController::stop() {
    motors->stop();
}

void MotionController::moveForward(float cm) {    
    odometer->enable();  
    speedCtl->enable();
    motors->rightForward();
    motors->leftForward();
    waitForDistance(cm); 
    odometer->disable();
    speedCtl->disable();   
}

void MotionController::moveBackwards(float cm) {            
    motors->rightBackwards();
    motors->leftBackwards();
    waitForDistance(cm);    
}


void MotionController::waitForDistance(float cm) {
    motors->setRightPulseLength(initialRightPulseLength);
    motors->setLeftPulseLength(initialLeftPulseLength);
    
     

    
    int targetTicks = (int) ceil(cm / (TWO_PI * 3.15) * 195);    
    bool rightDone = false;
    bool leftDone = false;
    do { 
        rightDone = Odometer::rightInt >= targetTicks;
        leftDone = Odometer::leftInt >= targetTicks;
        if (rightDone) {
            motors->stopRight(); 
            speedCtl->disable();
        }

        if (leftDone) {
            motors->stopLeft();
            speedCtl->disable();
        } 
        //speedCtl->updatePID();
    } while (!leftDone || !rightDone);
    
    motors->stop();    
}