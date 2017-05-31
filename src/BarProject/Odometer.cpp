#include "Odometer.h"

volatile int Odometer::leftInt;
volatile int Odometer::rightInt;
volatile unsigned long Odometer::rightTime;
volatile unsigned long Odometer::leftTime;
volatile double Odometer::leftAngularVelocity;
volatile double Odometer::rightAngularVelocity;
SpeedControl* Odometer::theSpeedCtl;


Odometer::Odometer(int leftInterruptPin, int rightInterruptPin) : 
leftInterruptPin(leftInterruptPin),
rightInterruptPin(rightInterruptPin) { }

void Odometer::leftISR() {
    Odometer::encoderISR(&leftTime, leftInt, leftAngularVelocity, 5);
}

void Odometer::rightISR() {
     Odometer::encoderISR(&rightTime, rightInt, rightAngularVelocity, 5);
}

void Odometer::encoderISR(
    volatile unsigned long* time, 
    volatile int& interrupts, 
    volatile double& angularVelocity,    
    int interruptThreshold) {

    if (*time == 0) {
        *time = millis();
    }
    
    interrupts++;
    if (interrupts % interruptThreshold == 0) {
        *time = millis() - *time;
        angularVelocity = (((float)interruptThreshold / 195.0f) * TWO_PI) / (*time / 1000.0);
        *time = millis();
        theSpeedCtl->updatePID();
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


