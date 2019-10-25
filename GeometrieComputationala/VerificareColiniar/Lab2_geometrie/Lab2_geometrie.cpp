// Lab2_geometrie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

class Point {
private:
	double x, y, z;
	static bool areEqual(Point A, Point B) {
		if (A.x == B.x && A.y == B.y && A.z == B.z) {
			return true;
		}
		return false;
	}
public:
	static double a;
	Point(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	static bool onTheSameLine(Point A1, Point A2, Point A3) {
		if (areEqual(A1, A2) || areEqual(A1, A3) || areEqual(A2, A3)) {
			return true;
		}

		// A3 - A1 == a * (A2 - A1)
		// Finding a
		if (A2.x - A1.x) {
			a = (A3.x - A1.x) / (A2.x - A1.x);
		}
		else if (A2.y - A1.y) {
			a = (A3.y - A1.y) / (A2.y - A1.y);
		}
		else if (A2.z - A1.z) {
			a = (A3.z - A1.z) / (A2.z - A1.z);
		}

		// Verfying the equations
		bool sameLine = true;
		if ((A3.x - A1.x) != a * (A2.x - A1.x)) {
			sameLine = false;
		}
		if ((A3.y - A1.y) != a * (A2.y - A1.y)) {
			sameLine = false;
		}
		if ((A3.z - A1.z) != a * (A2.z - A1.z)) {
			sameLine = false;
		}

		return sameLine;
	}

	static void writeOneAsTheOthers(Point A1, Point A2, Point A3) {
		if (!onTheSameLine(A1, A2, A3)) {
			return;
		}

		if (areEqual(A1, A2) && areEqual(A1, A3) && areEqual(A2, A3)) {
			cout << "A1 = A2 = A3 = (" << A1.x << ", " << A1.y << ", " << A1.z << ")\n";
			return;
		}
		if (areEqual(A1, A2)) {
			cout << "A1 = (1 * A2) + (0 * A3) = (" << A2.x << ", " << A2.y << ", " << A2.z << ")\n";
			return;
		}
		if (areEqual(A1, A3)) {
			cout << "A1 = (1 * A3) + (0 * A2) = (" << A3.x << ", " << A3.y << ", " << A3.z << ")\n";
			return;
		}
		if (areEqual(A3, A2)) {
			cout << "A3 = (1 * A2) + (0 * A1) = (" << A2.x << ", " << A2.y << ", " << A2.z << ")\n";
			return;
		}

		cout << "A3 = (1-a) * A1 + (a * A2) = (1-" << a << ") * (" << A1.x << ", " << A1.y << ", " << A1.z << ") + (" << a << "* (" << A2.x << ", " << A2.y << ", " << A2.z << ")) = ";
		cout << "(" << (1 - a) * A1.x + (a * A2.x) << ", " << (1 - a) * A1.y + (a * A2.y) << ", " << (1 - a) * A1.z + (a * A2.z) << ")\n";

	}
};
double Point::a = 0;

int main()
{
	auto A1 = new Point(0, 0, 0);
	auto A2 = new Point(0, 0, 0);
	auto A3 = new Point(0, 0, 1);

	if (Point::onTheSameLine(*A1, *A2, *A3)) {
		cout << "Puncte coliniare\n";
	}
	else {
		cout << "Punctele nu sunt coliniare\n";
	}

	Point::writeOneAsTheOthers(*A1, *A2, *A3);
}
