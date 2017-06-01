#include "RouteExecutor.h"
#include <Arduino.h>

RouteExecutor::RouteExecutor(MotionController* motion) : motion(motion) {}

void RouteExecutor::executeRoute(const char* route) {        
    int i = 0;
    char current = currentDirection;    
    char next = route[i++];
    while (next != '\n') {        
        transition(current, next);
        current = next;
        next = route[i++];
    }
    motion->rotateWithSign(360);
}

void RouteExecutor::transition(char from, char to) {
    float rotation = rotationLookup[from][to];
    motion->rotateWithSign(rotation);
    delay(stepDelayMs);
    //Here we can perform corrections for the rotation, by querying
    //the distance or ticks traveled by each wheel to take note of 
    //the expected distance traveled vs the actual distance.
    //*BUT* we should delegate this responsibility to the
    //MotionController, which should be aware of the position error.
    motion->moveForward(tileSizeCm);
    //Same as above
    delay(stepDelayMs);
}