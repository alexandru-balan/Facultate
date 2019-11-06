#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Point.h"

using namespace std;

class Segment
{
private:
	Point A, B;
public:
	Segment();
	Segment(Point A, Point B);
	Point getA();
	Point getB();

	static void Intersection(Segment A, Segment B);
	static bool PointInSegment(Point A, Segment S);
};

