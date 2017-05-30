#ifndef MYARDUINOPROJECT_ODOMETER_H
#define MYARDUINOPROJECT_ODOMETER_H

#include <Arduino.h>
#include "MotorDriver.h"

class Odometer {
        
public:
	Odometer(int leftInterruptPin, int rightInterruptPin);
        void enable();
        void disable();
        
        static MotorDriver* motors;        
        static volatile int leftInt;
        static volatile int rightInt;	

        static void leftISR();
        static void rightISR();
private:        
        int leftInterruptPin;
        int rightInterruptPin;                
};

#endif