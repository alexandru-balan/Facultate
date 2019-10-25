#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double calculeazaElement(int dim, int i, int j, double carry) {
	if (dim == 2) {
		int small[2][2]; small[0][0] = 1;  small[0][1] = 2; small[1][0] = 3; small[1][1] = 4;
		carry += small[i][j];
		return carry;
	}

	if (i < dim / 2) {
		if (j < dim / 2) {
			// Cadranul 1
			carry += calculeazaElement(dim / 2, i, j, 0);
		}
		else {
			// Cadranul 2
			carry += calculeazaElement(dim / 2, i, j -= (dim / 2), 1 * pow(2, dim / 2));
		}
	}
	else {
		if (j < dim / 2) {
			// Cadranul 3
			carry += calculeazaElement(dim / 2, i -= (dim / 2), j, 2 * pow(2, dim / 2));
		}
		else {
			// Cadranul 4
			carry += calculeazaElement(dim / 2, i -= (dim / 2), j -= (dim / 2), 3 * pow(2, dim / 2));
		}
	}

	return carry;
}

int main()
{
	int i, j, dim;
	cout << "Dimensiunea tablei (2^N): N = ";
	cin >> dim;
	cout << "i = ";
	cin >> i;
	cout << "j = ";
	cin >> j;

	dim = pow(2, dim);

	cout << calculeazaElement(dim, i, j, 0) << endl;;

	return 0; 
}