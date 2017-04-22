#ifndef MYARDUINOPROJECT_UDPSERVER_H
#define MYARDUINOPROJECT_UDPSERVER_H

#include <WiFiUdp.h>

class UdpServer {

    public:
        UdpServer(int port);
        void begin();
        void checkForPackets();

    private:
        int port;
        char inBuffer[127];
        WiFiUDP udp;

};

#endif //MYARDUINOPROJECT_UDPSERVER_H