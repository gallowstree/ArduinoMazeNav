#ifndef MYARDUINOPROJECT_ODOMETER_H
#define MYARDUINOPROJECT_ODOMETER_H

#include <Arduino.h>
#include "SpeedControl.h"

class Odometer {
        
public:
	Odometer(float wheelRadius, int resolution, int leftInterruptPin, int rightInterruptPin);
        void enable();
        void disable();
        float getRightDistance();
        float getLeftDistance();
        float getAvgDistance();
        float getMaxDistance();
        
        static SpeedControl* leftSpeedCtl;
        static SpeedControl* rightSpeedCtl;

        static volatile double leftAngularVelocity;
        static volatile double rightAngularVelocity;
        
        static volatile int leftInt;
        static volatile int rightInt;	

        static volatile unsigned long rightTime;
        static volatile unsigned long leftTime;

        static void leftISR();
        static void rightISR();
private:
        float wheelRadius;
        float resolution;
        
        int leftInterruptPin;
        int rightInterruptPin;

        float calculateDistance(float interrupts);
        
        
};

#endif