#include "Odometer.h"

volatile int Odometer::leftInt;
volatile int Odometer::rightInt;

Odometer::Odometer(int leftInterruptPin, int rightInterruptPin) : 
leftInterruptPin(leftInterruptPin),
rightInterruptPin(rightInterruptPin) { }

void Odometer::leftISR() {
    leftInt++;
    Serial.print("l: ");
    Serial.println(leftInt);
    motors->stopLeft();   
}

void Odometer::rightISR() {
    rightInt++;
    Serial.print("r: ");
    Serial.println(rightInt);
    motors->stopRight();             
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


