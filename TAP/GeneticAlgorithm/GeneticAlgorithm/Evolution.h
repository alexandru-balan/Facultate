#include "Individual.h"
#include <vector>
#include <ctime>
#include <random>

using namespace std;

#pragma once
class Evolution
{
private:
	int numberOfIndividuals;
	pair<int, int> interval;
	int intervalPrecision;
	double crossoverProbabilty;
	double mutationProbability;
	int numberOfStages;
	vector<Individual> population;
	vector<double> cumulativeProbabilities;
	
	double function(double x) {
		return -(pow(x, 2)) + x + 2;
	}

	int FindInterval(double value);

public:
	// Constructors
	Evolution();
	Evolution(int numberOfIndividuals, pair<int, int> interval, int intervalPrecision, double crossoverProbabilty, double mutationProbabilty, int numberOfStages);

	// Printing
	void PrintPopulation();
};

