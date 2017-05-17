#include "Odometer.h"

volatile int Odometer::leftInt;
volatile int Odometer::rightInt;
SpeedControl* Odometer::leftSpeedCtl;
SpeedControl* Odometer::rightSpeedCtl;

Odometer::Odometer(float wheelRadius, int resolution, int leftInterruptPin, int rightInterruptPin) : 
wheelRadius(wheelRadius),
resolution(resolution),
leftInterruptPin(leftInterruptPin),
rightInterruptPin(rightInterruptPin) { }


void Odometer::leftISR() {

    if (leftTime == 0)
        leftTime = millis();

    leftInt++;    
    if (leftInt % 10 == 0) {
        leftTime = (millis() - leftTime);        
        leftAngularVelocity = ((10.0 / 195.0f) * TWO_PI) / (leftTime/ 1000.0);                
        leftTime = millis();
        leftSpeedCtl->updatePID();
    }
}

void Odometer::rightISR() {
    if (rightTime == 0)
        rightTime = millis();

    rightInt++;    
    
    if (rightInt % 10 == 0) {
        rightTime = (millis() - rightTime);        
        rightAngularVelocity = ((10.0 / 195.0f) * TWO_PI) / (rightTime / 1000.0);
        rightTime = millis();
        rightSpeedCtl->updatePID(); 
    }       
}

void Odometer::enable() {
    Odometer::leftInt = 0;
    Odometer::rightInt = 0;
    Odometer::leftTime = 0;
    Odometer::rightTime = 0;
    attachInterrupt(digitalPinToInterrupt(leftInterruptPin), &Odometer::leftISR, RISING);
    attachInterrupt(digitalPinToInterrupt(rightInterruptPin), &Odometer::rightISR, RISING);    
}

void Odometer::disable() {
    detachInterrupt(digitalPinToInterrupt(leftInterruptPin));
    detachInterrupt(digitalPinToInterrupt(rightInterruptPin));    
}

float Odometer::getRightDistance() {
    return calculateDistance((float)Odometer::rightInt);
}

float Odometer::getLeftDistance() {
    return calculateDistance((float)Odometer::leftInt);
}

float Odometer::getAvgDistance() {
    return ( getLeftDistance() + getRightDistance() ) / 2.0f;
}

float Odometer::getMaxDistance() {
    return max(getLeftDistance(), getRightDistance());
}

float Odometer::calculateDistance(float interrupts) {
    return TWO_PI * (interrupts / resolution) * wheelRadius;
}


