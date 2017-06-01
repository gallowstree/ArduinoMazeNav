#ifndef MYARDUINOPROJECT_WIFI_CLIENT_H
#define MYARDUINOPROJECT_WIFI_CLIENT_H

#include <SPI.h>
#include <SoftwareSerial.h> 
#include "SparkFunESP8266WiFi.h"
#include "SparkFunESP8266Server.h"

//TO-DO: probably will want to make this an interface and extract implementation
//details to subclass ESP8266WifiConnection.
//**OR** leave the class WifiConnection and just create an interface that acts as 
//a wrapper for the ESP8266 (or any other wifi module)
class WifiConnection {

	public:

		WifiConnection();
		void Begin();

	private:
		
		// const char *ssid = "i like your squanch!";
		// const char *psk = "s@t@n@s666";	
		const char *ssid = "TURBONETT_0B2C35";
		const char *psk = "g@t0sc0nw1f1";	

		void initializeESP8266();	
		void connectESP8266();
		void displayConnectInfo();
};

#endif