#include "FileLogger.h"

#include <string>

using namespace std;

FileLogger::FileLogger(string filename)
{
	_file.open(filename, ofstream::trunc);
	if (!_file.is_open())
	{
		throw runtime_error("Could not open file \"" + filename + "\"");
	}
}

FileLogger::~FileLogger()
{
	if (_file.is_open())
	{
		_file.flush();
		_file.close();
	}
}

void FileLogger::Log(string message)
{
	_file << message;
}

void FileLogger::LogLine(string message)
{
	_file << message << endl;
}

void FileLogger::LogLine()
{
	_file << endl;
}
