#ifndef MYARDUINOPROJECT_ODOMETER_H
#define MYARDUINOPROJECT_ODOMETER_H

#include <Arduino.h>
#include "MotorDriver.h"
#include "SpeedControl.h"
class Odometer {
        
public:
	Odometer(int leftInterruptPin, int rightInterruptPin);
        void enable();
        void disable();
        
        static MotorDriver* motors;        
        static volatile int leftInt;
        static volatile int rightInt;	

        static SpeedControl* theSpeedCtl;        
        static volatile double leftAngularVelocity;
        static volatile double rightAngularVelocity;
        static volatile unsigned long rightTime;
        static volatile unsigned long leftTime;

        static void leftISR();
        static void rightISR();
        static void encoderISR(volatile unsigned long* time, volatile int& interrupts, volatile double& angularVelocity, int interruptThreshold);
private:        
        int leftInterruptPin;
        int rightInterruptPin;                
};

#endif