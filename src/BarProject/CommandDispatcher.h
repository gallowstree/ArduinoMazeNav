#ifndef MYARDUINOPROJECT_CMD_DISPATCHER_H
#define MYARDUINOPROJECT_CMD_DISPATCHER_H

#include "MotionController.h"

class CommandDispatcher {
public:
	CommandDispatcher(MotionController* motion);
	void handleMessage(char* data);
	//void sendMessage(char* data);

private:
	void handleMotorCmd(char * data);	
	MotionController* motionController;
};

#endif