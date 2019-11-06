#include "Point.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point& A)
{
	this->x = A.x;
	this->y = A.y;
}

double Point::getX()
{
	return x;
}

double Point::getY()
{
	return y;
}

bool Point::CompareX(Point A, Point B)
{
	if (A.x != B.x) {
		return A.x < B.x;
	}
	else {
		return A.y < B.y;
	}
}

Point& Point::operator=(const Point& A)
{
	this->x = A.x;
	this->y = A.y;

	return *this;
}

bool Point::operator==(const Point& A)
{
	if (x == A.x && y == A.y) {
		return true;
	}

	return false;
}

ostream& operator << (ostream& o, const Point& A) {
	o << "(" << A.x << ", " << A.y << ")\n";
	return o;
}
