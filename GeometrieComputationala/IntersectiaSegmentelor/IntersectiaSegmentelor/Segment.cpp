#include "Segment.h"


Segment::Segment()
{
	this->A = Point();
	this->B = Point();
}

Segment::Segment(Point A, Point B)
{
	this->A = A;
	this->B = B;
}

Point Segment::getA()
{
	return A;
}

Point Segment::getB()
{
	return B;
}

void Segment::Intersection(Segment S1, Segment S2)
{
	// Computing the ecuations for both segments
	// S1
	double a1 = 1.0 / (double)(S1.getB().getX() - S1.getA().getX());
	double b1 = -1.0 / (double)(S1.getB().getY() - S1.getA().getY());
	double c1 = (double)(-S1.getA().getX() / (S1.getB().getX() - S1.getA().getX())) + (double)(S1.getA().getY() / (S1.getB().getY() - S1.getA().getY()));

	// S2
	double a2 = 1.0 / (double)(S2.getB().getX() - S2.getA().getX());
	double b2 = -1.0 / (double)(S2.getB().getY() - S2.getA().getY());
	double c2 = (double)(-S2.getA().getX() / (S2.getB().getX() - S2.getA().getX())) + (double)(S2.getA().getY() / (S2.getB().getY() - S2.getA().getY()));

	// Computing the determinant
	double delta = (a1 * b2) - (b1 * a2);

	if (delta) {
		double x = ((-c1 * b2) - (b1 * -c2)) / delta;
		double y = ((a1 * -c2) - (-c1 * a2)) / delta;

		Point Inter(x, y);
		
		if (Segment::PointInSegment(Inter, S1) && Segment::PointInSegment(Inter, S2)) {
			cout << Inter;
			return;
		}
		else {
			cout << "Segmentele nu se intersecteaza\n";
		}
	}
	else {
		if ((a1 * c2) - (c1 * a2) || (b1 * c2) - (c1 * b2)) { // Rank 2
			cout << "Segmentele nu se intersecteaza\n";
			return;
		}
		else {
			vector<Point> v1 = vector<Point>();
			v1.push_back(S1.A); v1.push_back(S1.B); v1.push_back(S2.A); v1.push_back(S2.B);
			
			sort(v1.begin(), v1.end(), Point::CompareX);

			if ((v1[1] == S1.A || v1[1] == S1.B) && ((v1[2] == S2.A || v1[2] == S2.B))) {
				cout << "Intersectia este segmentul: \n";
				cout << v1[1] << v1[2];
				return;
			}

			if ((v1[1] == S2.A || v1[1] == S2.B) && ((v1[2] == S1.A || v1[2] == S1.B))) {
				cout << "Intersectia este segmentul: \n";
				cout << v1[1] << v1[2];
				return;
			}

			cout << "Segmentele nu se intersecteaza\n";
			return;
		}
	}
}

bool Segment::PointInSegment(Point A, Segment S)
{
	double x1S = S.getA().getX();
	double x2S = S.getB().getX();
	double y1S = S.getA().getY();
	double y2S = S.getB().getY();

	double dist1 = abs(A.getX() - x1S) + abs(A.getY() - y1S);
	double dist2 = abs(A.getX() - x2S) + abs(A.getY() - y2S);
	double distTotal = abs(x1S - x2S) + abs(y1S - y2S);

	if (dist1 + dist2 == distTotal) {
		return true;
	}
	else {
		return false;
	}

}
