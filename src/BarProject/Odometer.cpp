#include "Odometer.h"

volatile int Odometer::leftInt;
volatile int Odometer::rightInt;
volatile unsigned long Odometer::rightTime;
volatile unsigned long Odometer::leftTime;
volatile double Odometer::leftAngularVelocity;
volatile double Odometer::rightAngularVelocity;
volatile int16_t Odometer::encValRight;
volatile int16_t Odometer::encValLeft;
int8_t Odometer::lookup_table[16];
SpeedControl* Odometer::theSpeedCtl;


Odometer::Odometer(int leftInterruptPinA, int leftInterruptPinB, int rightInterruptPinA, int rightInterruptPinB) : 
leftInterruptPinA(leftInterruptPinA),
leftInterruptPinB(leftInterruptPinB),
rightInterruptPinA(rightInterruptPinA),
rightInterruptPinB(rightInterruptPinB) { }

void Odometer::leftISR() {    
    Odometer::encoderISR(&leftTime, leftInt, encValLeft, encMaskLeft, leftAngularVelocity, 5);
}

void Odometer::rightISR() {    
     Odometer::encoderISR(&rightTime, rightInt, encValRight, encMaskRight, rightAngularVelocity, 5);
}

void Odometer::encoderISR(
    volatile unsigned long* time, 
    volatile int& interrupts,
    volatile int16_t& encVal, 
    int16_t encMask, 
    volatile double& angularVelocity,    
    int interruptThreshold) {

    if (*time == 0) {
        *time = millis();
    }
    
    encVal = encVal << 2;
    encVal = encVal | ((PIND & encMask) >> ( encMask == encMaskLeft ? 0 : 2)); //Left encoder doesn't need right-shift 
 
    interrupts = interrupts + lookup_table[encVal & 0b1111];    
    
    if (interrupts % interruptThreshold == 0) {
        *time = millis() - *time;
        angularVelocity = (((float)interruptThreshold / 920.0f) * TWO_PI) / (*time / 1000.0);
        *time = millis();
        theSpeedCtl->updatePID();
    }

}

void Odometer::enable() {
    Odometer::leftInt = 0;
    Odometer::rightInt = 0;  
    Odometer::leftTime = 0;
    Odometer::rightTime = 0;  
    Odometer::encValRight = 0;
    Odometer::encValLeft = 0;
    attachInterrupt(digitalPinToInterrupt(leftInterruptPinA), &Odometer::leftISR, CHANGE);  
    attachInterrupt(digitalPinToInterrupt(leftInterruptPinB), &Odometer::leftISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(rightInterruptPinA), &Odometer::rightISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(rightInterruptPinB), &Odometer::rightISR, CHANGE);    
}

void Odometer::disable() {
    detachInterrupt(digitalPinToInterrupt(leftInterruptPinA));
    detachInterrupt(digitalPinToInterrupt(leftInterruptPinB));
    detachInterrupt(digitalPinToInterrupt(rightInterruptPinA));    
    detachInterrupt(digitalPinToInterrupt(rightInterruptPinB));  
}


