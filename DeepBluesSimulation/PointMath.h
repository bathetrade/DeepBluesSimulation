#ifndef POINT_MATH_H
#define POINT_MATH_H

#include "Point.h"

#include <cmath>

int GetDistance(Point p1, Point p2)
{
	int xDistance = abs(p1.X - p2.X);
	int yDistance = abs(p1.Y - p2.Y);

	//"Necrodancer distance"; total number of squares away, ignoring diagonals
	return xDistance + yDistance;
}
#endif
