#include "Individual.h"

string Individual::MakeBinary(long double number, int length)
{
	string sign("0");
	int exponent;
	int integerPart;
	deque<int> binaryInteger;	
	deque<int> binaryFractional(length, 0);
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
	long double fractionalPart = number - integerPart;
	for (int i = 0; i < length; ++i) {
		if (fractionalPart == 0) {
			break;
		}
		binaryFractional.push_back(floor(fractionalPart * 2));
		fractionalPart *= 2;

		if (fractionalPart > 1) {
			fractionalPart -= 1.0;
		}
	}

	while (binaryFractional.size() > length)
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
			while (binaryFractional.size() < length) {
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
		if (binaryFractional.size() > length) {
			while (binaryFractional.size() > length) {
				binaryFractional.pop_back();
			}
		}
		else if (binaryFractional.size() < length) {
			while (binaryFractional.size() < length) {
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

long double Individual::FromBinary(string binary)
{
	long double result = 0.0;

	int sign;
	int exponent = 0;
	long double fractional = 0.0;
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
	for (int i = length - 1; i >= 0; --i) {
		fractional += (binary.front() - '0') * pow(2, i);
		binary.erase(binary.begin());
	}
	while (fractional > 1) {
		fractional /= 10;
	}

	// Combine the numbers
	result = (long double)pow(-1, sign) * (1 + fractional) * (long double)pow(2, exponent);

	return result;
}

Individual::Individual()
{
	numericalValue = 0;
	binaryValue.assign(32, '0');
	selectionProbability = 0.0;
	length = 0;
}

Individual::Individual(long double number, int prec, int a, int b)
{
	this->numericalValue = number;
	// Finding length
	double n = 2;
	int i = 1;

	length = log2((b - a) * pow(10, prec));

	this->binaryValue = MakeBinary(number, length);
	this->selectionProbability = 0;
}

long double Individual::GetNumericalValue()
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
	this->binaryValue = MakeBinary(number, length);
}

void Individual::ChangeBinary(string binary)
{
	this->binaryValue = binary;
	this->numericalValue = FromBinary(binary);
}

long double Individual::GetSelectionProbability()
{
	return this->selectionProbability;
}

void Individual::SetSelectionProbability(long double prob)
{
	this->selectionProbability = prob;
}
