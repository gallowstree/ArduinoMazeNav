#ifndef MYARDUINOPROJECT_WIFI_CLIENT_H
#define MYARDUINOPROJECT_WIFI_CLIENT_H

#include <SPI.h>
#include <SoftwareSerial.h> 
#include "ESP8266/SparkFunESP8266WiFi.h"

//TO-DO: probably will want to make this an interface and extract implementation
//details to subclass ESP8266WifiConnection.
//**OR** leave the class WifiConnection and just create an interface that acts as 
//a wrapper for the ESP8266 (or any other wifi module)
class WifiConnection {

public:

	WifiConnection();
	void Begin();

private:
	
	const char *ssid = "wonderland";
	const char *psk = "starstuff";	
	//ESP8266Class esp8266;

	void initializeESP8266();	
	void connectESP8266();
	void displayConnectInfo();
};

#endif

