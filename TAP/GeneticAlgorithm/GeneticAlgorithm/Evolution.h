#include "Individual.h"
#include <vector>
#include <ctime>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;

#pragma once
class Evolution
{
private:
	int numberOfIndividuals;
	pair<int, int> interval;
	int intervalPrecision;
	long double crossoverProbabilty;
	long double mutationProbability;
	int numberOfStages;
	vector<Individual> population;
	vector<long double> cumulativeProbabilities;
	
	long double function(long double x) {
		return -(pow(x, 2)) + x + 2.0;
	}

	int FindInterval(long double value);

public:
	// Constructors
	Evolution();
	Evolution(int numberOfIndividuals, pair<int, int> interval, int intervalPrecision, long double crossoverProbabilty, long double mutationProbabilty, int numberOfStages);

	// Printing
	void PrintPopulation();
};

