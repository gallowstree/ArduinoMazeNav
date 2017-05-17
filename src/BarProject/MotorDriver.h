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

		void rightForward();
		void rightBackwards();
		void stopRight();

		void leftForward();
		void leftBackwards();
		void stopLeft();		

		int rightPwm = 2;
		double rightPulseLength = 0;
		int leftPwm = 3;
		double leftPulseLength = 0;


	private:
		int right0 = A0;
		int right1 = A1;
		int left0 = A2;
		int left1 = A3;		

};

#endif