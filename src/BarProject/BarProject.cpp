#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "DistanceSensor.h"
#include "WifiConnection.h"
#include "TcpDispatcher.h"
#include "ImuReader.h"
#include "MotionController.h"
#include "CommandDispatcher.h"
#include "Odometer.h"
#include "PidAutoTune.h"

DistanceSensor sensor1(A0, A1);
DistanceSensor sensor2(A2, A3);

double expectedSpeed = 10.0;

MotorDriver mtrDriver;
ImuReader imu;
Odometer odometer(3.15f, 195, 19, 18);
SpeedControl rightSpeedCtl(&Odometer::rightAngularVelocity, &mtrDriver.rightPulseLength, &expectedSpeed, mtrDriver.rightPwm);
SpeedControl leftSpeedCtl(&Odometer::leftAngularVelocity, &mtrDriver.leftPulseLength, &expectedSpeed, mtrDriver.leftPwm);
MotionController motion(&odometer, &imu, &mtrDriver, &rightSpeedCtl, &leftSpeedCtl);

WifiConnection conn;
CommandDispatcher cmdDispatcher(&motion);
TcpDispatcher tcpDispatcher(4420, &cmdDispatcher);

float prevLeftV = 0;
float prevRightV = 0;
float prevLeft = 0;
float prevRight = 0;

volatile unsigned long Odometer::leftTime;
volatile unsigned long Odometer::rightTime;
volatile double Odometer::leftAngularVelocity;
volatile double Odometer::rightAngularVelocity;


void setup() {

	Serial.begin(9600);
	Serial.println("Starting up :3");
	Wire.begin();
	delay(1000);
	
	//conn.Begin();
	//tcpDispatcher.begin();	

	Odometer::leftTime = 0;
	Odometer::rightTime = 0;
	Odometer::leftAngularVelocity = 0;
	Odometer::rightAngularVelocity = 0;	
	Odometer::rightSpeedCtl = &rightSpeedCtl;
	Odometer::leftSpeedCtl = &leftSpeedCtl;

	//test:
	mtrDriver.moveForward(); 
	odometer.enable();
	rightSpeedCtl.enable();
    leftSpeedCtl.enable();
	rightSpeedCtl.updatePID();
    leftSpeedCtl.updatePID();
			
	//imu.init();	
	
}

void printAngularVelocities() {
	float right = Odometer::rightAngularVelocity;
	float left = Odometer::leftAngularVelocity;

	if (prevLeftV != left || prevRightV != right) {
		Serial.print("Left: ");
		Serial.print(left);
		Serial.print("Right: ");
		Serial.println(right);
		prevLeftV = left;
		prevRightV = right;
	}
}

void printDistances() 
{
	float left = odometer.getLeftDistance();
	float right = odometer.getRightDistance();

	if (prevLeft != left || prevRight != right) {
		Serial.print("Left: ");
		Serial.print(left);
		Serial.print("Right: ");
		Serial.println(right);
		prevLeft = left;
		prevRight = right;
	}
}

void loop() {
	//tcpDispatcher.checkForPackets();
		
}
