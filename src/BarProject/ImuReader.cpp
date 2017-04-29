#include "ImuReader.h"
#include <Arduino.h>

void ImuReader::readImu() {
    Serial.begin(38400);

    // Set up the interrupt pin, its set as active high, push-pull
    pinMode(pinIn, INPUT);
    digitalWrite(pinIn, LOW);
    // pinMode(myLed, OUTPUT);
    // digitalWrite(myLed, HIGH);
}