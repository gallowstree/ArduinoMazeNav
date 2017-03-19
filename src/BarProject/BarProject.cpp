#include <Arduino.h>
#include <Wire.h>
#include "FooLib.h"
#include "DistanceSensor.h"

DistanceSensor sensor(A0, A1);

void setup() {

	Serial.begin(115200);
	delay(1000);

}

void loop() {
    float distance = sensor.GetDistanceCm();
    Serial.println(distance);
    delay(250);
}
