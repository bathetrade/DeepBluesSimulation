#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>

class ILogger
{
public:
	virtual void Log(std::string message) = 0;
	virtual void LogLine(std::string message) = 0;
	virtual void LogLine() = 0;
};

#endif