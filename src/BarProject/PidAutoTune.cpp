#include "PidAutoTune.h"

PidAutoTune::PidAutoTune(double input, double output, double setpoint):
input(input),
output(output),
setpoint(setpoint),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT), 
aTune(&input, &output) {     
    myPID.SetMode(AUTOMATIC);
    
    changeAutoTune(false);
    Serial.begin(9600);
}

void PidAutoTune::tune() {
    byte val = (aTune.Runtime());
  
    if (val != 0) {
        changeAutoTune(true);
        kp = aTune.GetKp();
        ki = aTune.GetKi();
        kd = aTune.GetKd();
        myPID.SetTunings(kp, ki, kd);
        print(false);
        return;
    }
    
    print(true);
    tune();
}

void PidAutoTune::changeAutoTune(boolean stop) {
    if(!stop) {
        aTune.SetNoiseBand(aTuneNoise);
        aTune.SetOutputStep(aTuneStep);
        aTune.SetLookbackSec((int)aTuneLookBack);
        ATuneModeRemember = myPID.GetMode();
    } else {
        aTune.Cancel();
        myPID.SetMode(ATuneModeRemember);
    }
}

void PidAutoTune::print(boolean tuning) {
  Serial.print("setpoint: ");Serial.print(setpoint); Serial.print(" ");
  Serial.print("input: ");Serial.print(input); Serial.print(" ");
  Serial.print("output: ");Serial.print(output); Serial.print(" ");
  if(tuning){
    Serial.println("tuning mode");
  } else {
    Serial.print("kp: ");Serial.print(myPID.GetKp());Serial.print(" ");
    Serial.print("ki: ");Serial.print(myPID.GetKi());Serial.print(" ");
    Serial.print("kd: ");Serial.print(myPID.GetKd());Serial.println();
  }
}