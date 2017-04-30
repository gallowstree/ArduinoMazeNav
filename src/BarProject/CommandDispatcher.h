#ifndef MYARDUINOPROJECT_CMD_DISPATCHER_H
#define MYARDUINOPROJECT_CMD_DISPATCHER_H

#include "MotorDriver.h"
#include "MotionController.h"

class CommandDispatcher {
public:
	CommandDispatcher(MotorDriver* motorDriver, MotionController* motion);
	void handleMessage(char* data);
	//void sendMessage(char* data);

private:
	void handleMotorCmd(char * data);
	MotorDriver* motorDriver;
	MotionController* motionController;
};

#endif