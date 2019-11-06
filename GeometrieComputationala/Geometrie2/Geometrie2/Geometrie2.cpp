#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Point {
private:
	int x, y;
public:
	Point() {
		x = 0;
		y = 0;
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	static bool xOrder(Point A, Point B) {
		return A.x < B.x;
	}

	friend ostream& operator << (ostream& o, const Point &P) {
		o << "(" << P.x << ", " << P.y << ")  ";
		return o;
	}
};

class ConvexHull {
private:
	vector<Point> Points;
	vector<Point> Triangle;
	Point sigle;

	int computeAreaTriangle(Point A, Point B, Point C) {
		return abs (A.getX() * (B.getY() - C.getY()) + B.getX() * (C.getY() - A.getY()) + C.getX() * (A.getY() - B.getY()));
	}

	bool onTheSameLine() {
		if (!computeAreaTriangle(Points[0], Points[1], Points[2]) && !computeAreaTriangle(Points[3], Points[1], Points[2])) {
			return true;
		}
		return false;
	}
	
	bool isTriangle() {
		int ABC = computeAreaTriangle(Points[0], Points[1], Points[2]);
		int ABD = computeAreaTriangle(Points[0], Points[1], Points[3]);
		int BCD = computeAreaTriangle(Points[1], Points[3], Points[2]);
		int ACD = computeAreaTriangle(Points[0], Points[3], Points[2]);

		vector<int> Areas; Areas.push_back(ABC); Areas.push_back(ABD); Areas.push_back(BCD); Areas.push_back(ACD);
		vector<int> sortedAreas = Areas;
		sort(sortedAreas.begin(), sortedAreas.end(), std::greater<>());

		int greatesAreaIndex = 0;
		for (int i = 0; i < Areas.size(); i++)
		{
			if (Areas[i] == sortedAreas[0]) {
				greatesAreaIndex = i;
			}
		}

		switch (greatesAreaIndex) {
		case 0:
			if (Areas[0] == Areas[1] + Areas[2] + Areas[3]) {
				Triangle.push_back(Points[0]); Triangle.push_back(Points[1]); Triangle.push_back(Points[2]);
				this->sigle = Points[3];
				return true;
			}
			else {
				return false;
			}
			break;
		case 1:
			if (Areas[1] == Areas[2] + Areas[0] + Areas[3]) {
				Triangle.push_back(Points[0]); Triangle.push_back(Points[1]); Triangle.push_back(Points[3]);
				this->sigle = Points[2];
				return true;
			}
			else {
				return false;
			}
			break;
		case 2:
			if (Areas[2] == Areas[1] + Areas[0] + Areas[3]) {
				Triangle.push_back(Points[3]); Triangle.push_back(Points[1]); Triangle.push_back(Points[2]);
				this->sigle = Points[0];
				return true;
			}
			else {
				return false;
			}
			break;
		case 3:
			if (Areas[3] == Areas[1] + Areas[2] + Areas[0]) {
				Triangle.push_back(Points[0]); Triangle.push_back(Points[3]); Triangle.push_back(Points[2]);
				this->sigle = Points[1];
				return true;
			}
			else {
				return false;
			}
			break;
		default:
			return false;
		}

	}

	int computeSideOfLine(Point A, Point B, Point C) {
		int sign = 0;
		if ((B.getX() - A.getX()) * (C.getY() - A.getY()) - (B.getY() - A.getY()) * (C.getX() - A.getX()) < 0) {
			sign = -1;
		}
		else if ((B.getX() - A.getX()) * (C.getY() - A.getY()) - (B.getY() - A.getY()) * (C.getX() - A.getX()) > 0) {
			sign = 1;
		}

		return sign;
	}

public:
	ConvexHull(vector<Point> Points) {
		this->Points = vector<Point>();

		this->Points = Points;
	}

	void giveSets() {
		if (onTheSameLine()) {
			cout << "Punctele sunt coliniare\n";
			sort(Points.begin(), Points.end(), Point::xOrder);
			cout << "I = { " << Points[0] << ", " << Points[3] << "}\n";
			cout << "J = { " << Points[1] << ", " << Points[2] << "}\n";
			return;
		}
		else if (isTriangle()) {
			cout << "Acoperirea convexa este un triunghi\n";
			cout << "I = { ";
			for (int i = 0; i < Triangle.size(); ++i) {
				cout << Triangle[i] << ", ";
			}
			cout << "\b\b\b";
			cout << "}\n";
			cout << "J = { " << this->sigle << "}\n";
		}
		else {
			cout << "Acoperirea convexa este un patrulater convex\n";
			bool foundDiagonals = false;
			if (computeSideOfLine(Points[0], Points[1], Points[2]) != computeSideOfLine(Points[0], Points[1], Points[3])) {
				// We found the two diagonals
				cout << "I = { " << Points[0] << ", " << Points[1] << "}\n";
				cout << "J = { " << Points[2] << ", " << Points[3] << "}\n";
				return;
			}

			if (computeSideOfLine(Points[0], Points[2], Points[1]) != computeSideOfLine(Points[0], Points[2], Points[3])) {
				// We found the two diagonals
				cout << "I = { " << Points[0] << ", " << Points[2] << "}\n";
				cout << "J = { " << Points[1] << ", " << Points[3] << "}\n";
				return;
			}

			if (computeSideOfLine(Points[0], Points[3], Points[1]) != computeSideOfLine(Points[0], Points[3], Points[2])) {
				// We found the two diagonals
				cout << "I = { " << Points[0] << ", " << Points[3] << "}\n";
				cout << "J = { " << Points[1] << ", " << Points[2] << "}\n";
				return;
			}
		}
		
	}

};

int main()
{
	Point A(0, 0);
	Point B(2, 2);
	Point C(3, 3);
	Point D(1, 1);
	
	vector<Point> Points; Points.push_back(A); Points.push_back(B); Points.push_back(C); Points.push_back(D);

	ConvexHull conv(Points);

	conv.giveSets();

	return 0;
}
