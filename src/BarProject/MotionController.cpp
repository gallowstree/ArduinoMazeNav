#include "MotionController.h"

MotionController::MotionController(Odometer* odometer, ImuReader* imu, MotorDriver* motors) : 
imu(imu),
motors(motors), 
odometer(odometer) {}

void MotionController::rotate(float degrees, bool clockwise) {
   
}

void MotionController::stop() {
    motors->stop();
}

void MotionController::moveForward(float cm) {    
    motors->moveForward();
    waitForDistance(cm);
    motors->stop();
}

void MotionController::moveBackwards(float cm) {
    motors->moveBackwards();
    waitForDistance(cm);
    motors->stop();
}

void MotionController::waitForDistance(float cm) {
    odometer->enable();
    while (odometer->getMaxDistance() < cm) {
        
    }
    odometer->disable();
}