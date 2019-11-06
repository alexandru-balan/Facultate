#include <iostream>
#include <vector>
#include <algorithm>
#include "Point.h"
#include "Segment.h"

using namespace std;

int main()
{
    // Points
	Point A1(1,1);
	Point A2(3,3);
	Point A3(2,2);
	Point A4(4,4);

	// Segments
	Segment S1(A1, A2);
	Segment S2(A3, A4);

	Segment::Intersection(S1, S2);

	return 0;
}