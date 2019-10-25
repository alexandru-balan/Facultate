#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int value;
	int stackNb;
};

vector<int> readVector(const char* file) {
	ifstream f(file);
	vector<int> list = vector<int>();

	if (f.is_open()) {
		int n; f >> n;
		for (int i = 0; i < n; i++)
		{
			int x; f >> x;
			list.push_back(x);
		}

		f.close();
	}

	return list;
}

void printVector(vector<int> list) {
	cout << "Original: ";
	for (int i = 0; i < list.size(); ++i) {
		cout << list[i] << " ";
	}
	cout << endl;
}

vector<deque<int>> decompose(vector<int> list) {
	vector<deque<int>> toReturn;
	deque<int> start = deque<int>();
	start.push_back(list[0]);
	toReturn.push_back(start);
	for (int i = 1; i < list.size(); ++i) {
		bool newdeque = true;
		for (int j = 0; j < toReturn.size(); ++j) {
			if (toReturn[j].back() > list[i]) {
				newdeque = false;
				toReturn[j].push_back(list[i]);
				break;
			}
		}
		if (newdeque) {
			deque<int> s = deque<int>();
			s.push_back(list[i]);
			toReturn.push_back(s);
		}
	}

	return toReturn;
}

void printParts(vector<deque<int>> parts) {
	cout << "-----------------------------" << endl;
	for (int i = 0; i < parts.size(); i++)
	{
		for (int j = 0; j < parts[i].size(); ++j) {
			cout << parts[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------" << endl;
}

vector<node> getBases(vector<deque<int>> &parts) {
	vector<node> bases;
	for (int i = 0; i < parts.size(); ++i) {
		node n; n.value = parts[i].back(); n.stackNb = i;
		bases.push_back(n);
		parts[i].pop_back();
	}
	return bases;
}

bool myGreaterFunction(node A, node B) {
	return A.value >= B.value;
}

void mySort(vector<node> heap, int n, vector<deque<int>> parts) {
	for (int i = 0; i < n; ++i) {
		cout << heap.front().value << " ";
		node N = heap.front();
		pop_heap(heap.begin(), heap.end(), myGreaterFunction); heap.pop_back();
		
		// Creating new node to push
		if (!parts[N.stackNb].empty()) {
			node newNode; newNode.value = parts[N.stackNb].back(); newNode.stackNb = N.stackNb;
			heap.push_back(newNode); push_heap(heap.begin(), heap.end(), myGreaterFunction);
			parts[N.stackNb].pop_back();
		}

	}
}

int main()
{
	vector<int> list = readVector("date.txt");
	printVector(list);

	vector<deque<int>> parts = decompose(list);
	printParts(parts);

	// Constructing the heap
	vector<node> heapbase = getBases(parts);

	make_heap(heapbase.begin(), heapbase.end(), myGreaterFunction);
	
	mySort(heapbase, list.size(), parts);

	return 0;
}