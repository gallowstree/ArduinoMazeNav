#include <Arduino.h>
#include <Wire.h>
#include "DistanceSensor.h"
#include "WifiConnection.h"
#include "TcpDispatcher.h"
#include <string.h>
#include "ImuReader.h"

DistanceSensor sensor1(A0, A1);
DistanceSensor sensor2(A2, A3);
TcpDispatcher dispatcher(4420);
ImuReader imu;

void setup() {

	Serial.begin(9600);
	Serial.println("Starting up :3");
	Wire.begin();
	delay(1000);

	WifiConnection conn;
	conn.Begin();
	dispatcher.begin();
	imu.init();
	imu.start();
}

void loop() {
    /*float distance = sensor1.GetDistanceCm();
    Serial.println(distance);
    delay(250);*/

	dispatcher.checkForPackets();	
	imu.tick();
	Serial.println(imu.rotation);
}
