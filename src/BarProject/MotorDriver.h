#ifndef MYARDUINOPROJECT_MOTORDRIVER_H
#define MYARDUINOPROJECT_MOTORDRIVER_H

#include <Arduino.h>

class MotorDriver {

	public:
		MotorDriver();

		void stop();		
		void rightForward();
		void rightBackwards();
		void stopRight();

		void leftForward();
		void leftBackwards();
		void forward();
		void backwards();
		void rotate(bool clockwise);
		void stopLeft();		

		int rightPwm = 3;
		double rightPulseLength = 0;
		int leftPwm = 2;
		double leftPulseLength = 0;		

		void setRightPulseLength(double l);
		void setLeftPulseLength(double l);

	private:
		int right0 = A2;
		int right1 = A3;
		int left0 = A0;
		int left1 = A1;		

};

#endif