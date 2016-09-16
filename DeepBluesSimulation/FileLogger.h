#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include "ILogger.h"

#include <fstream>

class FileLogger : public ILogger
{
public:
	FileLogger(std::string);
	~FileLogger();

	virtual void Log(std::string message);
	virtual void LogLine(std::string message);
	virtual void LogLine();

private:
	std::ofstream _file;
};

#endif