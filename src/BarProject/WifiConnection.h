#ifndef MYARDUINOPROJECT_WIFI_CLIENT_H
#define MYARDUINOPROJECT_WIFI_CLIENT_H

#include <SPI.h>
#include <WiFi.h>

class WifiConnection {

public:

	WifiConnection();
	void Begin();

private:
	
	char ssid[17] = "TURBONETT_0B2C35";
	char pass[13] = "g@t0sc0nw1f1";	
	int status = WL_IDLE_STATUS;
};

#endif

