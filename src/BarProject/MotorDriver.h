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

	private:
		int right0 = A0;
		int right1 = A1;
		int left0 = A2;
		int left1 = A3;
		int pulseDuration = 50;
};

#endif