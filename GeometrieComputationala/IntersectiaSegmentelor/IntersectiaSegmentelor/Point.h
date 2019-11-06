#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Point
{
private:
	double x, y;
public:
	Point();
	Point(double x, double y);
	Point(const Point& A);
	double getX();
	double getY();
	static bool CompareX(Point A, Point B);
	Point& operator = (const Point& A);
	bool operator ==(const Point& A);
	friend ostream& operator <<(ostream& o, const Point& A);
};

