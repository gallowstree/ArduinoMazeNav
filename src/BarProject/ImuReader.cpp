#include "ImuReader.h"
#include <Arduino.h>

bool ImuReader::init() {    
    if (communicationTest()) {
        Serial.println(F("MPU9250 is online..."));
        //selfTest();
        myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);
        myIMU.initMPU9250();        
        Serial.println("MPU9250 initialized for active data mode....");
         // Get sensor resolutions, only need to do this once
        myIMU.getAres();
        myIMU.getGres();
        myIMU.getMres();
    }
}

void ImuReader::start() {
    rotation = 0;
    recording = true;
}

void ImuReader::stop() {
    recording = false;
}

void ImuReader::tick() {
    if (!recording) return;

    readData();    
    myIMU.delt_t = millis() - myIMU.count;
    
    if (myIMU.delt_t > 100) 
    {
        if(serialDebug) 
        {
            Serial.print("ax = ");  Serial.print((int)1000 * myIMU.ax);
            Serial.print("\tay = "); Serial.print((int)1000 * myIMU.ay);        
            Serial.print("\tmg");

            Serial.print("\tgz = "); Serial.print(myIMU.gz, 2);
            Serial.print("\tabs = "); Serial.print(abs(myIMU.gz));
            Serial.println("\tdeg/s");
        }

        if ( abs(myIMU.gz) > gyroThreshold ) {
            rotation += myIMU.delt_t/1000.0 * myIMU.gz;    
            rotation = static_cast<int>(rotation) % 360;
        }
            
        myIMU.count = millis();
        myIMU.sumCount = 0;
        myIMU.sum = 0;
    }
}

void ImuReader::readData() {
    if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
    {
        myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values

        // Now we'll calculate the accleration value into actual g's
        // This depends on scale being set
        myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes; // - myIMU.accelBias[0];
        myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes; // - myIMU.accelBias[1];
        myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes; // - myIMU.accelBias[2];

        myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values

        // Calculate the gyro value into actual degrees per second
        // This depends on scale being set
        myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
        myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
        myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;
    }

    myIMU.updateTime();
}

//Test communication with Accel & Gyro... not mag
bool ImuReader::communicationTest() {
  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  Serial.print(F("MPU9250 I AM 0x"));
  Serial.print(c, HEX);
  Serial.print(F(" I should be 0x"));
  Serial.println(0x71, HEX);
  delay(1000);
  return c == 0x71; 
}

void ImuReader::selfTest() {
    // Start by performing self test and reporting values
    myIMU.MPU9250SelfTest(myIMU.selfTest);
    Serial.print(F("x-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[0],1); Serial.println("% of factory value");
    Serial.print(F("y-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[1],1); Serial.println("% of factory value");
    Serial.print(F("z-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[2],1); Serial.println("% of factory value");
    Serial.print(F("x-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[3],1); Serial.println("% of factory value");
    Serial.print(F("y-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[4],1); Serial.println("% of factory value");
    Serial.print(F("z-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[5],1); Serial.println("% of factory value");
}