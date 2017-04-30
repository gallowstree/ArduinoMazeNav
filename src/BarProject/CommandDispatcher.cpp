#include "CommandDispatcher.h"
#include "StringUtils.h"
#include "string.h"
#include <Arduino.h>

CommandDispatcher::CommandDispatcher(MotorDriver* motors, MotionController* motion) : 
	motorDriver(motors), 
	motionController(motion) 
	{
		
	}

void CommandDispatcher::handleMessage(char* data) {

	// Serial.println("CommandDispatcher::handleMessage");
	
	int cmdTypeLength = indexOf(data, '\n', 0);

	if (cmdTypeLength != -1) {		
		auto cmdType = new char[cmdTypeLength + 1];	
		memset(cmdType, 0, cmdTypeLength + 1);
		memcpy(cmdType, data, cmdTypeLength);	

		// Serial.print("cmdType: ");
		// Serial.println(cmdType);		

		if (strcmp(cmdType, "MOTOR") == 0) {
			handleMotorCmd(data + cmdTypeLength + 1);
		}

		delete cmdType;
	}	
}

void CommandDispatcher::handleMotorCmd(char * data) {
	int actionLength = indexOf(data, '\n', 0);
	// Serial.println("handlingMotorcmd");
	if (actionLength != -1) {
		auto action = new char[actionLength + 1];	
		memset(action, 0, actionLength + 1);
		memcpy(action, data, actionLength);	

		// Serial.print("action: ");
		// Serial.println(action);

		if (strcmp(action, "STOP") == 0) {
			motorDriver->stop();
		} else if (strcmp(action, "FORWARD") == 0) {
			motorDriver->moveForward();
		} else if (strcmp(action, "BACKWARDS") == 0) {
			motorDriver->moveBackwards();
		} else if (strcmp(action, "CLOCKWISE") == 0) {
			motorDriver->rotate(true);
		} else if (strcmp(action, "COUNTERCLOCKWISE") == 0) {
			motorDriver->rotate(false);
		}

		delete action;
	}
}
