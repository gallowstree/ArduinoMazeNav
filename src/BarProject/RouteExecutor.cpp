#include "RouteExecutor.h"
#include <Arduino.h>

RouteExecutor::RouteExecutor(MotionController* motion) : motion(motion) {}

void RouteExecutor::executeRoute(const char* route) {    
    Serial.print("executingRoute: ");  
    Serial.println(route);
    int i = 0;
    char current = currentDirection;    
    char next = route[i++];

    Serial.print("Moving from ");
    Serial.print(current);
    Serial.print("to ");
    Serial.println(next);
    while (true) {
        Serial.print("next: ");       
        Serial.println(next); 
        transition(current, next);
        current = next;        
        next = route[i++];
        if (next > 3) break; //this is the newline xD
    }
    motion->rotateWithSign(360);
}

void RouteExecutor::transition(char from, char to) {
    float rotation = rotationLookup[from][to];
    motion->rotateWithSign(rotation);
    Serial.println("Done rotating!");
    delay(stepDelayMs);
    //Here we can perform corrections for the rotation, by querying
    //the distance or ticks traveled by each wheel to take note of 
    //the expected distance traveled vs the actual distance.
    //*BUT* we should delegate this responsibility to the
    //MotionController, which should be aware of the position error.
    Serial.println("Strarting to move!");
    motion->moveForward(tileSizeCm);
    Serial.println("Done moving!");
    //Same as above
    delay(stepDelayMs);
}