#include <Arduino.h>
#include <Wire.h>
#include "FooLib.h"
#include "DistanceSensor.h"
#include "WifiConnection.h"

DistanceSensor sensor1(A0, A1);
DistanceSensor sensor2(A2, A3);


void setup() {

	Serial.begin(9600);
	Serial.println("Hola putos!");
	delay(1000);

	WifiConnection conn;
	conn.Begin();
}

void loop() {
    /*float distance = sensor1.GetDistanceCm();
    Serial.println(distance);
    delay(250);*/
}
