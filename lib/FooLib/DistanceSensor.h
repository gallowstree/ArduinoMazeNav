//
// Created by Alvarado, Alejandro on 3/18/17.
//

#ifndef MYARDUINOPROJECT_DISTANCESENSOR_H
#define MYARDUINOPROJECT_DISTANCESENSOR_H


#include <Arduino.h>

const unsigned int MAX_DIST = 23200;

class DistanceSensor {

public:

    DistanceSensor(int trig, int echo);

    float GetDistanceCm();

private:

    int trig;
    int echo;

};


#endif //MYARDUINOPROJECT_DISTANCESENSOR_H
