#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

#pragma once
class Individual
{
private:
	double numericalValue;
	string binaryValue;
	double selectionProbability;

	string MakeBinary(double number);
	double FromBinary(string binary);

public:
	// Construtors
	Individual();
	Individual(double number);

	// SET & GET Methods
	double GetNumericalValue();
	string GetBinaryValue();
	void ChangeValue(int number); // This will also change the binary representation
	void ChangeBinary(string binary);
	double GetSelectionProbability();
	void SetSelectionProbability(double prob);
};

