#ifndef MYARDUINOPROJECT_TCPDISPATCHER_H
#define MYARDUINOPROJECT_TCPDISPATCHER_H

#include "SparkFunESP8266WiFi.h"
#include "CommandDispatcher.h"

class TcpDispatcher {

    public:
        TcpDispatcher(int port, CommandDispatcher* dispatcher);
        void begin();
        void checkForPackets();

    private:
        int port;               
        ESP8266Server server;
        char inBuffer[127];
        CommandDispatcher *dispatcher;        
};

#endif 