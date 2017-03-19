cmake_minimum_required(VERSION 3.6)
project(MyArduinoProject)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/)
INCLUDE_DIRECTORIES(/Applications/Arduino.app/Contents/Java/hardware/tools/avr/avr/include)
INCLUDE_DIRECTORIES(/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega/)
INCLUDE_DIRECTORIES(/Applications/Arduino.app/Contents/Java/libraries/Wifi/src/)
INCLUDE_DIRECTORIES(lib/)

set(SOURCE_FILES
        lib/BarLib/BarLib.cpp
        lib/BarLib/BarLib.h
        lib/FooLib/FooLib.cpp
        lib/FooLib/FooLib.h
        src/BarProject/BarProject.cpp
        src/FooProject/FooProject.cpp lib/Distance/DistanceSensor.cpp lib/Distance/DistanceSensor.h)

add_executable(MyArduinoProject ${SOURCE_FILES})