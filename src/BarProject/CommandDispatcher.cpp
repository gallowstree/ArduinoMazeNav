#include "CommandDispatcher.h"
#include "StringUtils.h"
#include "string.h"
#include <Arduino.h>

CommandDispatcher::CommandDispatcher(MotionController* motion, RouteExecutor* routeExec) : 	
	motionController(motion),
	routeExec(routeExec) 
	{
		
	}

void CommandDispatcher::handleMessage(char* data) {

	// Serial.println("CommandDispatcher::handleMessage");
	
	int cmdTypeLength = indexOf(data, '\n', 0);

	if (cmdTypeLength != -1) {		
		auto cmdType = new char[cmdTypeLength + 1];	
		memset(cmdType, 0, cmdTypeLength + 1);
		memcpy(cmdType, data, cmdTypeLength);	

		Serial.print("cmdType: ");
		Serial.println(cmdType);		

		if (strcmp(cmdType, "MOTOR") == 0) {			
			handleMotorCmd(data + cmdTypeLength + 1);
		} else if (strcmp(cmdType, "ROUTE") == 0) {
			handleRouteCmd(data + cmdTypeLength + 1);
		}

		delete[] cmdType;
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

		int cmdParamLength = indexOf(data, '\n', actionLength);
		float cmdParam = 0;

		if (cmdParamLength != -1) {
			auto paramStr = new char[cmdParamLength + 1];
			memset(paramStr, 0, cmdParamLength + 1);
			memcpy(paramStr, data + actionLength, cmdParamLength);	
			cmdParam = atof(paramStr);
			Serial.print("Param: ");
			Serial.println(cmdParam);
			delete[] paramStr;
		}		

		if (strcmp(action, "STOP") == 0) {
			motionController->stop();
		} else if (strcmp(action, "FORWARD") == 0) {
			motionController->moveForward(cmdParam);
		} else if (strcmp(action, "BACKWARDS") == 0) {
			motionController->moveBackwards(cmdParam);
		} else if (strcmp(action, "CLOCKWISE") == 0) {			
			motionController->rotate(cmdParam, true);
		} else if (strcmp(action, "COUNTERCLOCKWISE") == 0) {			
			motionController->rotate(cmdParam, false);
		}

		delete[] action;
	}
}

void CommandDispatcher::handleRouteCmd(char * data) {
		int actionLength = indexOf(data, '\n', 0);
		Serial.println("handling Routercmd");
		Serial.println(data);
		if (actionLength != -1) {
			auto action = new char[actionLength + 1];	
			memset(action, 0, actionLength + 1);
			memcpy(action, data, actionLength);	

			Serial.print("action: ");
			Serial.println(action);

			int cmdParamLength = indexOf(data, '\n', actionLength + 1);			
			Serial.print("cmdParamLength: ");
			Serial.println(cmdParamLength);
			if (cmdParamLength != -1) {
				auto paramStr = new char[cmdParamLength + 1];
				memset(paramStr, 0, cmdParamLength + 1);
				memcpy(paramStr, data + actionLength + 1, cmdParamLength);		

				for (int i = 0; i < cmdParamLength; i++) {
					Serial.println(paramStr[i]);
				}
				
				if (strcmp(action, "START") == 0) {
					routeExec->executeRoute(paramStr);
				}

				delete[] paramStr;
			}		

			delete[] action;
		}
	}

