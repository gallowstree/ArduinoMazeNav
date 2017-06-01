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
    beforeMoving();
    motors->rightForward();
    motors->leftForward();
    waitForDistance(cm); 
    afterMoving(); 
}

void MotionController::moveBackwards(float cm) {
    beforeMoving();       
    motors->rightBackwards();
    motors->leftBackwards();
    waitForDistance(cm);
    afterMoving();    
}

void MotionController::beforeMoving() {
    motors->setRightPulseLength(initialRightPulseLength);
    motors->setLeftPulseLength(initialLeftPulseLength);             
    odometer->enable();  
    speedCtl->enable(); 
}


void MotionController::afterMoving() {
    motors->setRightPulseLength(initialRightPulseLength);
    motors->setLeftPulseLength(initialLeftPulseLength);             
    odometer->enable();  
    speedCtl->enable(); 
}


void MotionController::waitForDistance(float cm) {    
    int targetTicks = (int) floor(cm / (TWO_PI * 3.16) * 195);    
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