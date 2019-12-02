#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> readMatrix(const char* file, int& k) {
	ifstream f(file);

	vector<vector<int>> Matrix;

	if (!f.is_open()) {
		return vector<vector<int>>();
	}
	else {
		int n, m;
		f >> n >> m;

		Matrix = vector<vector<int>>(n);

		for (int i = 0; i < n; ++i) {
			Matrix[i] = vector<int>(m);

			for (int j = 0; j < m; j++)
			{
				f >> Matrix[i][j];
			}
		}
	}

	f >> k;

	return Matrix;
}

void findGreatestAreaSquare(vector<vector<int>> Matrix, int k) {

	int max = -1;
	int line, column;
	int nrOfSquares = 0;

	/* Building an auxiliary matrix with just the last row and last column of the original one */
	vector<vector<int>> Sizes = vector<vector<int>>(Matrix.size());
	for (int i = 0; i < Sizes.size(); ++i) {
		Sizes[i] = vector<int>(Matrix[0].size());

		if (i == Sizes.size() - 1) {
			for (int j = 0; j < Matrix[0].size(); ++j) {
				Sizes[i][j] = abs(Matrix[i][j] - 1);
			}
		}

		Sizes[i][Matrix[0].size() - 1] = abs(1-Matrix[i][Matrix[0].size() - 1]);
	}

	for (int i = Sizes.size() - 2; i >= 0; --i) {
		for (int j = Sizes[0].size() - 2; j >= 0; --j) {
			if (Matrix[i][j] == 1) {
				Sizes[i][j] == 0;
			}
			else {
				Sizes[i][j] = min(Sizes[i][j + 1], min(Sizes[i + 1][j + 1], Sizes[i + 1][j])) + 1;

				if (Sizes[i][j] >= max) {
					max = Sizes[i][j];
					line = i;
					column = j;
				}

				/* Finding the number of squares with the dimension greater than a given number */
				if (Sizes[i][j] >= k) {
					int x = Sizes[i][j];
					while (x >= k)
					{
						nrOfSquares++;
						x--;
					}
				}
			}
		}
	}

	cout << "Dimension : " << max << endl;
	cout << "Coordinates of top left corner: " << "line = " << line + 1 << " column = " << column + 1 << endl;

	cout << "Number of squares with length greater or equal with " << k << " is: " << nrOfSquares << endl;
}

int main()
{
	int k;
	vector<vector<int>> Matrix = readMatrix("data.in", k);

	findGreatestAreaSquare(Matrix, k);
}