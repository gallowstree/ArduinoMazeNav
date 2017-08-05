#include "TcpDispatcher.h"
#include <Arduino.h>


TcpDispatcher::TcpDispatcher(int port, CommandDispatcher* cmd):
    port(port),
    dispatcher(cmd),
    server(ESP8266Server(port)) {}

void TcpDispatcher::begin() {
    this->server.begin();
}

void TcpDispatcher::checkForPackets() {
    ESP8266Client client = server.available(100);
    if (client) 
    {
        Serial.println(F("Client Connected!"));
        int i = 0;
        bool shouldCopy = false;
        memset(inBuffer, 0, sizeof(inBuffer));
        while (client.connected()) 
        {
            while (!client.available());
            
            char c = client.read();

            if (shouldCopy)
                inBuffer[i++] = c;
            if (!shouldCopy && c == ':')
                shouldCopy = true;                            
        }
        Serial.println("inBuffer:");
        Serial.println(inBuffer);
        //client.stop();

        dispatcher->handleMessage(inBuffer);
    }   
}