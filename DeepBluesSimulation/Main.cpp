#include <iostream>
#include <unordered_map>
#include "DeepBluesLevel.h"
#include "FileLogger.h"

using namespace std;

int main()
{
	FileLogger logger("C:\\users\\derek\\desktop\\deepblueslog.txt");
	Cadence cadence;
	DeepBluesLevel level(cadence, logger);
	level.Initialize();
	cin.get();
	return 0;
}