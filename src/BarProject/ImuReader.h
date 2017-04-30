#ifndef MYARDUINOPROJECT_IMU_READER_H
#define MYARDUINOPROJECT_IMU_READER_H

#include "MPU9250.h"



class ImuReader {
    public:
        bool init();
        void start();
        void tick();
        void stop();

        float rotation;
        
    private:
        bool communicationTest();
        void selfTest();
        void readData();
        MPU9250 myIMU;
        int pinIn;
        bool recording;    
        bool serialDebug = false;
        float gyroThreshold = 0.25;

};

#endif