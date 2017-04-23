#ifndef MYARDUINOPROJECT_CMD_DISPATCHER_H
#define MYARDUINOPROJECT_CMD_DISPATCHER_H

#include "MotorDriver.h"

class CommandDispatcher {
public:
	CommandDispatcher();
	void handleMessage(char* data);
	//void sendMessage(char* data);

private:
	void handleMotorCmd(char * data);
	MotorDriver motorDriver;
};

#endif