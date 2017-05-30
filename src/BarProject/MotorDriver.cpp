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

void MotorDriver::rightForward() {
    digitalWrite(right0, HIGH);
    digitalWrite(right1, LOW);
}

void MotorDriver::leftForward() {
    digitalWrite(left0, LOW);
    digitalWrite(left1, HIGH);
}

void MotorDriver::rightBackwards() {
    digitalWrite(right0, LOW);
    digitalWrite(right1, HIGH);
}

void MotorDriver::leftBackwards() {
    digitalWrite(left0, HIGH);
    digitalWrite(left1, LOW);
}

void MotorDriver::stopRight() {
    //Serial.println("stop right");
    digitalWrite(right0, LOW);
    digitalWrite(right1, LOW);
    setRightPulseLength(0.0);
}

void MotorDriver::stopLeft() {
    //Serial.println("stop left");
    digitalWrite(left0, LOW);
    digitalWrite(left1, LOW);
    setLeftPulseLength(0.0);
}

void MotorDriver::setRightPulseLength(double l) {
    rightPulseLength = l;
    analogWrite(rightPwm, rightPulseLength);
}

void MotorDriver::setLeftPulseLength(double l) {
    leftPulseLength = l;
    analogWrite(leftPwm, leftPulseLength);
}