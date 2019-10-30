#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Point {
private:
	double x, y;
public:
	Point() {
		x = 0; y = 0;
	}
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}

	static bool Compare(Point A, Point B) {
		if (A.x != B.x) {
			return A.x < B.x;
		}
		else {
			return A.y < B.y;
		}
	}

	static bool CompareY(Point A, Point B) {
		if (A.y != B.y) {
			return A.y < B.y;
		}
		else {
			return A.x < B.x;
		}
	}

	static double computeDistance(Point A, Point B) {
		return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
	}

	friend ostream& operator << (ostream& o, const Point& P) {
		o << "( " << P.x << ", " << P.y << ")\n";
		return o;
	}

	Point& operator =(const Point& P) {
		this->x = P.x;
		this->y = P.y;

		return *this;
	}
};

vector<Point> readPoints(const char* file) {
	ifstream f(file);
	vector<Point> Points = vector<Point>();

	if (f.is_open()) {
		int n; f >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			f >> x; f >> y;
			Point newPoint(x, y);
			Points.push_back(newPoint);
		}
	}

	return Points;
}

double getMinDistance(vector<Point>& Points, Point& a, Point& b) {
	if (Points.size() <= 3) {
		// Computing the minimal distance in a set of at most 3 points
		double maximal = DBL_MAX;
		for (int i = 1; i < Points.size(); ++i) {
			double value = Point::computeDistance(Points[i - 1], Points[i]);
			if (value <= maximal) {
				maximal = value;
				a = Points[i - 1];
				b = Points[i];
			}

		}

		sort(Points.begin(), Points.end(), Point::CompareY);

		return maximal;
	}

	vector<Point> leftPart = vector<Point>(); leftPart.assign(Points.begin(), Points.begin() + (Points.size() / 2));
	vector<Point> rightPart = vector<Point>(); rightPart.assign(Points.begin() + (Points.size() / 2), Points.end());
	double xOfLine = (leftPart.back().getX() + rightPart.front().getX()) / 2; // The x coordinate of the line separating the two sets of points


	// Recursively computing the min distance from left and right side
	Point AL, BL, AR, BR;
	double minLeft = getMinDistance(leftPart,AL,BL);
	double minRight = getMinDistance(rightPart,AR,BR);

	vector<Point> Merged(leftPart.size() + rightPart.size());

	merge(leftPart.begin(), leftPart.end(), rightPart.begin(), rightPart.end(), Merged.begin(), Point::CompareY);
	Points = Merged;

	// Now we must get the min distance (if it exists) from pairs that have a point in the left side and one in the right side
	double minDist = min(minLeft, minRight);

	if (minDist == minLeft) {
		a = AL;
		b = BL;
	}
	else {
		a = AR;
		b = BR;
	}

	vector<Point> Y = vector<Point>();

	// Building the Y
	for (int i = 0; i < Merged.size(); ++i) {
		if (abs(Merged[i].getX() - xOfLine) <= minDist) {
			Y.push_back(Merged[i]);
		}
	}

	for (int i = 0; i < Y.size(); ++i) {
		for (int j = i + 1; j < Y.size(); ++j) {
			if (j - i >= 16) {
				break;
			}
			double dist = Point::computeDistance(Y[i], Y[j]);
			if (dist <= minDist){
				minDist = dist;
				a = Y[i];
				b = Y[j];
			}
		}
	}

	return minDist;
}

int main()
{
    // Read the points
	vector<Point> Points = readPoints("grader_test11.in");
	
	// Sorting points by Ox
	sort(Points.begin(), Points.end(), Point::Compare);

	Point MinA, MinB;

	cout << getMinDistance(Points,MinA,MinB) << endl;

	cout << MinA << MinB;

	return 0;
}