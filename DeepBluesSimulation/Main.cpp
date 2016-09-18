#include <iostream>
#include <unordered_map>
#include "Dagger.h"
#include "DeepBluesLevel.h"
#include "Cadence.h"
#include "FileLogger.h"
using namespace std;

int main()
{
	FileLogger logger("C:\\users\\derek\\desktop\\deepblueslog.txt");

	Cadence cadence;
	cadence.SetPosition(Point(7,3));
	cadence.EquipWeapon(new Dagger());

	DeepBluesLevel level(cadence, logger);
	cout << "Initial board: " << endl;
	level.Initialize();
	level.PrintBoard();

	//Input loop
	while (cadence.GetHealth() > 0)
	{
		cout << "Enter 'up', 'right', 'down', or 'left':";
		string input;
		getline(cin, input);
		if (input == "up")
		{
			cadence.SetMove(Direction::UP);
		}
		else if (input == "right")
		{
			cadence.SetMove(Direction::RIGHT);
		}
		else if (input == "down")
		{
			cadence.SetMove(Direction::DOWN);
		}
		else if (input == "left")
		{
			cadence.SetMove(Direction::LEFT);
		}
		else if (input == "quit")
		{
			break;
		}
		else
		{
			cout << "Unrecognized input; not moving" << endl;
		}
		level.UpdateEntities();
		level.PrintBoard();
		cout << endl;
	}

	if (cadence.GetHealth() <= 0)
	{
		cout << "Cadence died!" << endl;
	}

	cin.get();
	return 0;
}