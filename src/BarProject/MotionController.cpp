#include "MotionController.h"
#include <math.h>

MotionController::MotionController(Odometer* odometer, MotorDriver* motors, SpeedControl* speedCtl) : 
motors(motors), 
odometer(odometer),
speedCtl(speedCtl){

}

void MotionController::rotate(float degrees, bool clockwise) {
    if (degrees == 0) 
        return;

    float rads = degrees * TWO_PI / 360.0f;
    float rotationRadius = 5.3;
    float targetDistance = rads * rotationRadius;
    beforeMoving();
    motors->rotate(clockwise);
    waitForDistance(targetDistance);
    afterMoving();
}

void MotionController::rotateWithSign(float degrees) {
    Serial.print("Rotating ");
    Serial.print(degrees);
    Serial.println(" degs");
    rotate(degrees, degrees > 0);
}

void MotionController::stop() {
    motors->stop();
}

void MotionController::moveForward(float cm) {        
    beforeMoving();
    motors->forward();
    waitForDistance(cm); 
    afterMoving(); 
}

void MotionController::moveBackwards(float cm) {
    beforeMoving();       
    motors->backwards();
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
            speedCtl->disable();
            motors->stopRight();
            motors->stopLeft();
            // motors->setLeftPulseLength(initialLeftPulseLength);
        }

        if (leftDone) {
            speedCtl->disable();
            motors->stopLeft();
            motors->stopRight();
            // motors->setLeftPulseLength(initialRightPulseLength);            
        } 
        //speedCtl->updatePID();
    } while (!leftDone && !rightDone);
    
    motors->stop();    
}