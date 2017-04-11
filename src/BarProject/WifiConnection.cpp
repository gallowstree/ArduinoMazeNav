#include "WifiConnection.h"


WifiConnection::WifiConnection() {}

void WifiConnection::Begin() {
	while (!Serial);

	//TODO: exceptions
	if (WiFi.status() == WL_NO_SHIELD) {
		Serial.println("WiFi shield not present");
		return;		
	}

	String fv = WiFi.firmwareVersion();
  	if (fv != "1.1.0") {
    	Serial.println("Please upgrade the firmware");
  	}

  	// attempt to connect to Wifi network:
	while (status != WL_CONNECTED) {
		Serial.print("Attempting to connect to WPA SSID: ");
		Serial.println(ssid);
		// Connect to WPA/WPA2 network:
		status = WiFi.begin(ssid, pass);

		// wait 10 seconds for connection:
		delay(10000);
	}

	Serial.print("You're connected to the network! YAY!");
}