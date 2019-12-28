#include "Individual.h"

string Individual::MakeBinary(double number)
{
	string sign("0");
	int exponent;
	int integerPart;
	deque<int> binaryInteger;
	deque<int> binaryFractional(23, 0);
	deque<int> binaryExponent;
	string binaryRepr;
	
	if (number < 0) {
		sign = "1";
		number = abs(number);
	}

	// Transforming the integer part
	integerPart = floor(number);
	while (integerPart != 0) {
		binaryInteger.push_front(integerPart % 2);
		integerPart /= 2;
	}
	if (binaryInteger.size() == 0) {
		binaryInteger.push_front(0);
	}
	integerPart = floor(number);

	// Transforming the fractional part
	double fractionalPart = number - integerPart;
	for (int i = 0; i < 23; ++i) {
		if (fractionalPart == 0) {
			break;
		}
		binaryFractional.push_back(floor(fractionalPart * 2));
		fractionalPart *= 2;

		if (fractionalPart > 1) {
			fractionalPart -= 1.0;
		}
	}

	while (binaryFractional.size() > 23)
	{
		binaryFractional.pop_front();
	}

	// Normalizing mantisa and computing exponent
	exponent = 0;
	if (binaryInteger.size() == 1) {
		if (binaryInteger.front() == 0) {
			while (binaryFractional.front() != 1) {
				exponent--;
				binaryFractional.pop_front();
			}
			binaryFractional.pop_front();
			exponent--;
			while (binaryFractional.size() < 23) {
				binaryFractional.push_front(0);
			}
		}
	}
	else {
		while (binaryInteger.size() > 1)
		{
			exponent++;
			int x = binaryInteger.back();
			binaryFractional.push_front(x);
		}
		if (binaryInteger.front() == 0) {
			while (binaryFractional.front() != 1)
			{
				exponent--;
				binaryFractional.pop_front();
			}
			binaryFractional.pop_front();
			exponent--;
		}
		if (binaryFractional.size() > 23) {
			while (binaryFractional.size() > 23) {
				binaryFractional.pop_back();
			}
		}
		else if (binaryFractional.size() < 23) {
			while (binaryFractional.size() < 23) {
				binaryFractional.push_front(0);
			}
		}
	}

	// Adjusting exponent
	exponent = exponent + 127;
	while (exponent != 0) {
		binaryExponent.push_front(exponent % 2);
		exponent /= 2;
	}
	while (binaryExponent.size() < 8) {
		binaryExponent.push_front(0);
	}

	// Constructing the 32-bit representation
	binaryRepr = sign;
	for (auto bit : binaryExponent) {
		if (bit == 0) {
			binaryRepr.push_back('0');
		}
		else {
			binaryRepr.push_back('1');
		}
	}
	for (auto bit : binaryFractional) {
		if (bit == 0) {
			binaryRepr.push_back('0');
		}
		else {
			binaryRepr.push_back('1');
		}
	}

	return binaryRepr;
}

double Individual::FromBinary(string binary)
{
	double result = 0.0;

	int sign;
	int exponent = 0;
	double fractional = 0.0;
	int x;

	// Get the sign
	if (binary.front() == '0') {
		sign = 0;
		binary.erase(binary.begin());
	}
	else {
		sign = 1;
		binary.erase(binary.begin());
	}

	// Get the exponent
	for (int i = 7; i >= 0; --i) {
		exponent += (binary.front() - '0') * pow(2, i);
		binary.erase(binary.begin());
	}
	exponent -= 127;

	// Get the fractional part
	for (int i = 22; i >= 0; --i) {
		fractional += (binary.front() - '0') * pow(2, i);
		binary.erase(binary.begin());
	}
	while (fractional > 1) {
		fractional /= 10;
	}

	// Combine the numbers
	result = pow(-1, sign) * (1 + fractional) * pow(2, exponent);

	return result;
}

Individual::Individual()
{
	numericalValue = 0;
	binaryValue.assign(32, '0');
	selectionProbability = 0.0;
}

Individual::Individual(double number)
{
	this->numericalValue = number;
	this->binaryValue = MakeBinary(number);
	this->selectionProbability = 0;
}

double Individual::GetNumericalValue()
{
	return this->numericalValue;
}

string Individual::GetBinaryValue()
{
	return this->binaryValue;
}

void Individual::ChangeValue(int number)
{
	this->numericalValue = number;
	this->binaryValue = MakeBinary(number);
}

void Individual::ChangeBinary(string binary)
{
	this->binaryValue = binary;
	this->numericalValue = FromBinary(binary);
}

double Individual::GetSelectionProbability()
{
	return this->selectionProbability;
}

void Individual::SetSelectionProbability(double prob)
{
	this->selectionProbability = prob;
}
