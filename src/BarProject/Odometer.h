#ifndef MYARDUINOPROJECT_ODOMETER_H
#define MYARDUINOPROJECT_ODOMETER_H

#include <Arduino.h>
#include "MotorDriver.h"
#include "SpeedControl.h"
class Odometer {
        
public:
	Odometer(int leftInterruptPinA, int leftInterruptPinB, int rightInterruptPinA, int rightInterruptPinB);
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
        static void encoderISR(volatile unsigned long* time, volatile int& interrupts, volatile int16_t& encVal, int16_t encMask, volatile double& angularVelocity, int interruptThreshold);
private:        
        int leftInterruptPinA;
        int leftInterruptPinB;
        int rightInterruptPinA;
        int rightInterruptPinB;    
        static int8_t lookup_table[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  
        volatile static int16_t encValRight;
        volatile static int16_t encValLeft;         
        static const int16_t encMaskRight = 0x000C;
        static const int16_t encMaskLeft  = 0x0003;         
};

#endif