#ifndef MYARDUINOPROJECT_CMD_H
#define MYARDUINOPROJECT_CMD_H

class Command {
public:
	const CommandType type;
	Command(const CommandType type, char* data);
}

class enum CommandType 
{
	motor
}

#endif