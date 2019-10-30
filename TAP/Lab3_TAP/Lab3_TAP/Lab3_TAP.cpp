#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*Inversiuni semnificative*/

int merge(int* vs, int* vd, int*& vector, int ds, int dd) {

	int x = 0; //Nr de inversiuni introduse la un pas
	int nrOfInversions = 0; //Nr total de inversiuni
	int i = 0, j = 0, k = 0; //indici de parcurgere ai vectorilor vs,vd, vector
	while (i < ds && j < dd) {
		if (vs[i] < 2 * vd[j]) { // Alegere stanga
			nrOfInversions += x;
			i++;
		}
		if (vd[j] < 2 * vs[i]) { //Alegere dreapta
			vector[k] = vd[j];
			x++;
			j++;
		}
	}

	if (j == dd) { //Sunt numarate resutl de inversiuni din stanga
		while (i < ds)
		{
			nrOfInversions += x;
			i++;
		}
	}

	i = 0; j = 0;
	while (i < ds && j < dd) {
		if (vs[i] < vd[j]) { // Alegere stanga
			vector[k] = vs[i];
			i++;
			k++;
		}
		if (vd[j] < vs[i]) { //Alegere dreapta
			vector[k] = vd[j];
			x++;
			j++;
			k++;
		}
	}

	if (i == ds) { //Daca s-a terminat vector stanga dar nu si dreapta => nu afecteaza inversiunile
		while (j < dd)
		{
			vector[k] = vd[j];
			j++;
			k++;
		}
	}

	if (j == dd) { //Sunt numarate resutl de inversiuni din stanga
		while (i < ds)
		{
			vector[k] = vs[i];
			k++;
			i++;
		}
	}

	return nrOfInversions;
}


int solve(int* vector, int n) {
	if (n == 1) {
		return 0;
	}

	int vs[50];
	int vd[50];

	for (int i = 0; i < n / 2; ++i) {
		vs[i] = vector[i];
	}

	int j = 0;
	for (int i = n / 2; i < n; ++i) {
		vd[j] = vector[i];
		++j;
	}

	int nrs = solve(vs, n / 2);
	int nrd = solve(vd, n - (n / 2));
	/*vs si vd sunt vectorii combinati,
	* vector este vectorul initial care va deveni vectorul rezultat al combinarii
	* n/2 si n-(n/2) sunt dimensiunile vs si vd
	*/
	int nrm = merge(vs, vd, vector, (n / 2), (n - n / 2));

	int NOI = nrs + nrm + nrd;

	return NOI;
}

int main()
{
	/*Se declara vectorul initial si numarul sau de elemente*/
	int* vector;
	int n;

	/*Citim numarul de elemente*/
	cout << "n = ";
	cin >> n;

	/*Se aloca spatiu pentru vector*/
	vector = new int[n];

	/*Se citeste vectorul*/
	for (int i = 0; i < n; ++i) {
		cout << "v[" << i << "] = ";
		cin >> vector[i];
	}

	/*Variabila NOI stocheaza numarul de inversiuni returnat
	 *de functia solve(int*,int);
	 */
	int NOI = solve(vector, n);

	for (int i = 0; i < n; ++i) {
		cout << vector[i] << " ";
	}
	cout << endl;

	/*Se afiseaza rezultatul*/
	cout << "Nr inversiuni semnifcative: " << NOI << endl;

	return 0;
}