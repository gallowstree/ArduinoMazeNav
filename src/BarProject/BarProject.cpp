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

DistanceSensor sensor1(A0, A1);
DistanceSensor sensor2(A2, A3);


MotorDriver mtrDriver;
ImuReader imu;
Odometer odometer(20, 21, 18, 19);
SpeedControl speedCtl(&Odometer::leftAngularVelocity, &Odometer::rightAngularVelocity, &mtrDriver);
MotionController motion(&odometer, &mtrDriver, &speedCtl);
RouteExecutor routeExec(&motion);

WifiConnection conn;
CommandDispatcher cmdDispatcher(&motion, &routeExec);
TcpDispatcher tcpDispatcher(4420, &cmdDispatcher);

float prevLeft = 0;
float prevRight = 0;

MotorDriver* Odometer::motors;

void setup() {
	Serial.begin(9600);
	Serial.println("Starting up :3");
	Wire.begin();
	delay(1000);
	
	// conn.Begin();
	// tcpDispatcher.begin();

	Odometer::motors = &mtrDriver;	
	Odometer::theSpeedCtl = &speedCtl;
	odometer.enable();
}

void printInterruptCounters() {
	int left = Odometer::leftInt;
	int right = Odometer::rightInt;

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
	printInterruptCounters();	
	
}
