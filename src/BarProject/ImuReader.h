#ifndef MYARDUINOPROJECT_IMU_READER_H
#define MYARDUINOPROJECT_IMU_READER_H

#include "MPU9250.h"

class ImuReader {
    public:
        void readImu();

    private:
        MPU9250 myIMU;
        int pinIn;

};

#endif