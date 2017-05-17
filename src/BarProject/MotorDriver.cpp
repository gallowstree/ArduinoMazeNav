#include "MotorDriver.h"

MotorDriver::MotorDriver() {
	pinMode(right0, OUTPUT);
    pinMode(right1, OUTPUT);
    pinMode(left0, OUTPUT);
    pinMode(left1, OUTPUT);
    pinMode(rightPwm, OUTPUT);
    pinMode(leftPwm, OUTPUT);    
    analogWrite(rightPwm, rightPulseLength);
    analogWrite(leftPwm, leftPulseLength);
}

void MotorDriver::stop()
{
	Serial.println("stop");
	stopRight();
    stopLeft();
}

void MotorDriver::moveForward()
{
	Serial.println("moveForward");
	rightForward();
    leftForward();
}

void MotorDriver::moveBackwards()
{
	Serial.println("moveBackwards");
	rightBackwards();
    leftBackwards();
}

void MotorDriver::rotate(bool clockwise)
{
	// Serial.println("rotate");
    if (clockwise) {
        rightForward();
        leftBackwards();
    } else {
        rightBackwards();
        leftForward();
    }    	
}

void MotorDriver::rightForward() {
    digitalWrite(right0, LOW);
    digitalWrite(right1, HIGH);
}

void MotorDriver::rightBackwards() {
    digitalWrite(right0, HIGH);
    digitalWrite(right1, LOW);
}

void MotorDriver::stopRight() {
    digitalWrite(right0, LOW);
    digitalWrite(right1, LOW);
    rightPulseLength = 0;
}

void MotorDriver::leftForward() {
    digitalWrite(left0, HIGH);
    digitalWrite(left1, LOW);
    leftPulseLength = 0;
}

void MotorDriver::leftBackwards() {
    digitalWrite(left0, LOW);
    digitalWrite(left1, HIGH);
}

void MotorDriver::stopLeft() {
    digitalWrite(left0, LOW);
    digitalWrite(left1, LOW);
}

void MotorDriver::setPower(float multiplier) {    
    analogWrite(rightPwm,rightPulseLength);
    analogWrite(leftPwm, leftPulseLength);
}

float MotorDriver::getPower() {
    return 1;
}