#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <sstream>

using namespace std;

struct Point
{
public:
	Point()
	{
		X = 0;
		Y = 0;
	}
	Point(int x, int y)
	{
		X = x;
		Y = y;
	}
	Point operator+(Point p) const
	{
		return Point(X + p.X, Y + p.Y);
	}
	Point operator-(Point p) const
	{
		return Point(X - p.X, Y - p.Y);
	}
	bool operator==(Point p) const
	{
		return X == p.X && Y == p.Y;
	}
	std::string ToString() const
	{
		std::stringstream s;
		s << "(" << X << "," << Y << ")";
		return s.str();
	}

	int X;
	int Y;
};

#endif