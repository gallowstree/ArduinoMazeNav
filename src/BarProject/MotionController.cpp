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
    float r = 0, l = 0;
    while ((r = odometer->getRightDistance()) < cm ||
           (l = odometer->getLeftDistance()) < cm) {
        if (r >= cm) motors->stopRight();
        if (l >= cm) motors->stopLeft();
    }
    odometer->disable();
}