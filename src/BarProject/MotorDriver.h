#ifndef MYARDUINOPROJECT_MOTORDRIVER_H
#define MYARDUINOPROJECT_MOTORDRIVER_H

#include <Arduino.h>

class MotorDriver {

	public:
		MotorDriver();
		void stop();
		void moveForward();
		void moveBackwards();
		void rotate(bool clockwise);	
		void setPower(float multiplier);	
		float getPower();		

	private:
		int right0 = A0;
		int right1 = A1;
		int rightPwm = 2;
		int left0 = A2;
		int left1 = A3;
		int leftPwm = 3;
		int pulseLength = 255;
		float rightPulseFraction = 0.8;
		float leftPulseFraction = 0.8;
};

#endif