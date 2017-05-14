#include "Odometer.h"

volatile float Odometer::leftInt;
volatile float Odometer::rightInt;



Odometer::Odometer(float wheelRadius, int resolution, int leftInterruptPin, int rightInterruptPin) : 
wheelRadius(wheelRadius),
resolution(resolution),
leftInterruptPin(leftInterruptPin),
rightInterruptPin(rightInterruptPin) { }


void Odometer::leftISR() {
    leftInt++;    
}

void Odometer::rightISR() {
    rightInt++;    
}

void Odometer::enable() {
    Odometer::leftInt = 0;
    Odometer::rightInt = 0;
    attachInterrupt(digitalPinToInterrupt(leftInterruptPin), &Odometer::leftISR, RISING);
    attachInterrupt(digitalPinToInterrupt(rightInterruptPin), &Odometer::rightISR, RISING);
}

void Odometer::disable() {
    detachInterrupt(digitalPinToInterrupt(leftInterruptPin));
    detachInterrupt(digitalPinToInterrupt(rightInterruptPin));
}

float Odometer::getRightDistance() {
    return calculateDistance(Odometer::rightInt);
}

float Odometer::getLeftDistance() {
    return calculateDistance(Odometer::leftInt);
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
