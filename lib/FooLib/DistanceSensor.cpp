//
// Created by Alvarado, Alejandro on 3/18/17.
//

#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int trig, int echo) :
        trig(trig),
        echo(echo) {
    pinMode(trig, OUTPUT);
    digitalWrite(trig, LOW);
}

float DistanceSensor::GetDistanceCm() {
    unsigned long t1;
    unsigned long t2;
    unsigned long pulse_width;
    float cm;

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    while ( digitalRead(echo) == 0 );

    t1 = micros();
    while ( digitalRead(echo) == 1);
    t2 = micros();
    pulse_width = t2 - t1;


    cm = pulse_width / 58.0f;

    if ( pulse_width > MAX_DIST ) {
        return -1;
    }

    return cm;
}