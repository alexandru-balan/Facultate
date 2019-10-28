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

double getMinDistance(vector<Point> Points, Point& a, Point& b) {
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

		return maximal;
	}

	vector<Point> leftPart = vector<Point>(); leftPart.assign(Points.begin(), Points.begin() + (Points.size() / 2));
	vector<Point> rightPart = vector<Point>(); rightPart.assign(Points.begin() + (Points.size() / 2), Points.end());

	// Recursively computing the min distance from left and right side
	Point AL, BL, AR, BR;
	double minLeft = getMinDistance(leftPart,AL,BL);
	double minRight = getMinDistance(rightPart,AR,BR);

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

	double xOfLine = (leftPart.back().getX() + rightPart.front().getX()) / 2; // The x coordinate of the line separating the two sets of points

	vector<Point> Y = vector<Point>();
	vector<Point> Y2 = vector<Point>();

	// Building the Y and Y2 sets of points that are at the most minDist distance from the dividing line
	for (int i = leftPart.size() - 1; i >= 0; --i) {
		if (xOfLine - leftPart[i].getX() < minDist) {
			Y.push_back(leftPart[i]);
		}
		else {
			break;
		}
	}

	for (int i = 0; i < rightPart.size(); ++i) {
		if (rightPart[i].getX() - xOfLine < minDist) {
			Y2.push_back(rightPart[i]);
		}
		else {
			break;
		}
	}

	// Now that we have those points, we exhaustively compute the minimal distance of all the pairs that have one point in Y and the other in Y2
	for (int i = 0; i < Y.size(); ++i) {
		for (int j = 0; j < Y2.size(); ++j) {
			double value = Point::computeDistance(Y[i], Y2[j]);
			if (value < minDist) {
				minDist = value;
				a = Y[i];
				b = Y2[j];
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