#include "MotionController.h"
#include <math.h>

MotionController::MotionController(Odometer* odometer, MotorDriver* motors) : 
motors(motors), 
odometer(odometer){

}

void MotionController::rotate(float degrees, bool clockwise) {
    float rads = degrees * TWO_PI / 360;
    float rotationRadius = 7.8;
    float targetDistance = rads * rotationRadius;
    waitForDistance(targetDistance,  Motion(motors, clockwise ? Motion::clockwise : Motion::counterclockwise, leftPulseLength, rightPulseLength));
}

void MotionController::stop() {
    motors->stop();
}

void MotionController::moveForward(float cm) {
    Motion motion(motors, Motion::forward, leftPulseLength, rightPulseLength);
    waitForDistance(cm, motion);    
}

void MotionController::moveBackwards(float cm) {        
    Motion motion(motors, Motion::backwards, leftPulseLength, rightPulseLength);
    waitForDistance(cm, motion);    
}


void MotionController::waitForDistance(float cm, Motion m) {
    odometer->enable();   
    
    int targetTicks = (int) ceil(cm / (TWO_PI * 3.15) * 195);
    Serial.print("target: ");
    Serial.println(targetTicks);
    
    while (Odometer::rightInt < targetTicks || Odometer::leftInt < targetTicks) {
        
        //if (Odometer::rightInt <= Odometer::leftInt)
        if (Odometer::rightInt <= targetTicks) {
            m.right();
        }
        
        //if (Odometer::leftInt <= Odometer::rightInt)
        if (Odometer::leftInt <= targetTicks) {
            m.left();
        }
    }

    motors->stop();
    odometer->disable();
}