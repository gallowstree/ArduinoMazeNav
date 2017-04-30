#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "DistanceSensor.h"
#include "WifiConnection.h"
#include "TcpDispatcher.h"
#include "ImuReader.h"
#include "MotionController.h"
#include "CommandDispatcher.h"

DistanceSensor sensor1(A0, A1);
DistanceSensor sensor2(A2, A3);
MotorDriver mtrDriver;
ImuReader imu;
WifiConnection conn;
MotionController motion(&imu, &mtrDriver);
CommandDispatcher cmdDispatcher(&mtrDriver, &motion);
TcpDispatcher tcpDispatcher(4420, &cmdDispatcher);


void initializeObjects() {

}

void setup() {

	Serial.begin(9600);
	Serial.println("Starting up :3");
	Wire.begin();
	delay(1000);
	
	conn.Begin();
	tcpDispatcher.begin();
	imu.init();
	imu.start();
}

void loop() {
    /*float distance = sensor1.GetDistanceCm();
    Serial.println(distance);
    delay(250);*/

	tcpDispatcher.checkForPackets();	
	imu.tick();
	Serial.println(imu.rotation);
}
