#ifndef MYARDUINOPROJECT_CMD_DISPATCHER_H
#define MYARDUINOPROJECT_CMD_DISPATCHER_H

#include "MotionController.h"
#include "RouteExecutor.h"

class CommandDispatcher {
public:
	CommandDispatcher(MotionController* motion, RouteExecutor* routeExec);
	void handleMessage(char* data);	
	//void sendMessage(char* data);

private:
	void handleMotorCmd(char * data);	
	void handleRouteCmd(char* data);
	MotionController* motionController;
	RouteExecutor* routeExec;
};

#endif