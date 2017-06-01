#ifndef MYARDUINOPROJECT_ROUTEEXECUTOR_H
#define MYARDUINOPROJECT_ROUTEEXECUTOR_H

#include "MotionController.h"

#define DIRECTION_LEFT 0
#define DIRECTION_UP 1
#define DIRECTION_RIGHT 2
#define DIRECTION_DOWN 3


class RouteExecutor {
        
public:
	RouteExecutor(MotionController* motion);
    void executeRoute(const char* route);
private:        
    void transition(char from, char to);
    MotionController* motion;
    float tileSizeCm = 25;
    int stepDelayMs = 500;
    char currentDirection = 0;
    const float rotationLookup[4][4] = {
    /*-------TO STATE --------*/
    //   L    U     R    D    // FROM STATE  
        {0  ,-90, 180, -90},  // L  
        {90,   0, -90, 180},  // U
        {180, 90,   0, -90},  // R
        {-90, 180, 90,   0}   // D 
    };
};

#endif