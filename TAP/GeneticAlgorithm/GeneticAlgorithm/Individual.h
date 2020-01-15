#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

#pragma once
class Individual
{
private:
	long double numericalValue;
	string binaryValue;
	long double selectionProbability;
	int length;

	string MakeBinary(long double number, int length);
	long double FromBinary(string binary);

public:
	// Construtors
	Individual();
	Individual(long double number, int prec, int a, int b);

	// SET & GET Methods
	long double GetNumericalValue();
	string GetBinaryValue();
	void ChangeValue(int number); // This will also change the binary representation
	void ChangeBinary(string binary);
	long double GetSelectionProbability();
	void SetSelectionProbability(long double prob);
};

