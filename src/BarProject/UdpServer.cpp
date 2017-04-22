#include "UdpServer.h"
#include <Arduino.h>


UdpServer::UdpServer(int port):
    port(port) {}

void UdpServer::begin() {
    int a = udp.begin(port);
    Serial.println(a);
    Serial.println("Waiting...");
}

void UdpServer::checkForPackets() {
    int packetSize = udp.parsePacket();
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    if (packetSize) {
        Serial.println(packetSize);
        Serial.println("yee");
    }
}