#include "Evolution.h"

int Evolution::FindInterval(double value)
{
	int middle = cumulativeProbabilities.size() / 2;
	int left = 0;
	int right = cumulativeProbabilities.size() - 1;

	while ((value > cumulativeProbabilities[middle] && value > cumulativeProbabilities[middle + 1]) || (value < cumulativeProbabilities[middle] && value < cumulativeProbabilities[middle - 1])) {
		if (value > cumulativeProbabilities[middle] && value > cumulativeProbabilities[middle + 1]) {
			left = middle + 1;
			middle = (left + right) / 2;
		}
		else if (value < cumulativeProbabilities[middle] && value < cumulativeProbabilities[middle - 1]) {
			right = middle - 1;
			middle = (left + right) / 2;
		}
	}

	if (value >= cumulativeProbabilities[middle] && value <= cumulativeProbabilities[middle + 1]) {
		return middle;
	}
	else if (value <= cumulativeProbabilities[middle] && value >= cumulativeProbabilities[middle - 1]) {
		return middle - 1;
	}
}

Evolution::Evolution()
{
	this->numberOfIndividuals = 0;
	this->interval = pair<int, int>(0, 0);
	this->intervalPrecision = 0;
	this->crossoverProbabilty = 0;
	this->mutationProbability = 0;
	this->numberOfStages = 0; 
	this->population = vector<Individual>();
	this->cumulativeProbabilities = vector<double>();
}

Evolution::Evolution(int numberOfIndividuals, pair<int, int> interval, int intervalPrecision, double _crossoverProbability, double _mutationProbability, int numberOfStages)
{
	this->numberOfIndividuals = numberOfIndividuals;
	this->interval = interval;
	this->intervalPrecision = intervalPrecision;
	this->crossoverProbabilty = _crossoverProbability;
	this->mutationProbability = _mutationProbability;
	this->numberOfStages = numberOfStages;
	this->population = vector<Individual>();
	this->cumulativeProbabilities = vector<double>();

	cumulativeProbabilities.push_back(0);

	double sumOfFunctions = 0.0;

	uniform_real_distribution<double> uniform(-1, 2);
	default_random_engine re;
	re.seed(time(NULL));
	for (int i = 0; i < numberOfIndividuals; ++i) {
		Individual individual(uniform(re));

		this->population.push_back(individual);
		sumOfFunctions += function(individual.GetNumericalValue());
	}

	for (int i = 0; i < population.size(); ++i) {
		population[i].SetSelectionProbability(function(population[i].GetNumericalValue()) / sumOfFunctions);

		double q = 0.0;
		for (int j = 0; j <= i; ++j) {
			q += population[j].GetSelectionProbability();
		}
		cumulativeProbabilities.push_back(q);
	}
}

void Evolution::PrintPopulation()
{
	vector<double> summary;
	for (int k = 0; k < numberOfStages; ++k) {
		
		for (unsigned int i = 0; i < population.size(); ++i) {
			cout << i + 1 << ":\t" << population[i].GetBinaryValue() << "\tx = " << population[i].GetNumericalValue() << "\tf = " << function(population[i].GetNumericalValue()) << endl;
		}

		cout << endl << "Probabilitatea de selectie:" << endl;
		for (int i = 0; i < population.size(); ++i) {
			cout << i + 1 << ":\t" << population[i].GetSelectionProbability() << endl;
		}

		cout << endl << "Intervale probabilitati de selectie" << endl;
		for (int i = 1; i < cumulativeProbabilities.size(); ++i) {
			cout << cumulativeProbabilities[i - 1] << "\t\t" << cumulativeProbabilities[i] << endl;
		}


		uniform_real_distribution<double> uniform(0, 1);
		default_random_engine re;
		uniform_int_distribution<int> uniformInt(0, 31);

		re.seed(time(NULL));

		vector<Individual> newPopulation;
		cout << endl << "Selectie:" << endl;
		for (int i = 0; i < population.size(); ++i) {
			// Generate u
			double u = uniform(re);

			// Binary search for u
			int interval = FindInterval(u);

			Individual individual(population[interval]);
			newPopulation.push_back(individual);

			cout << "u = " << u << "\t" << "Selectam cromozomul " << interval + 1 << endl;
		}
		population = newPopulation;

		cout << endl << "Dupa selectie: " << endl;
		for (unsigned int i = 0; i < population.size(); ++i) {
			cout << i + 1 << ":\t" << population[i].GetBinaryValue() << "\tx = " << population[i].GetNumericalValue() << "\tf = " << function(population[i].GetNumericalValue()) << endl;
		}

		// Crossover phase
		cout << endl << "Faza de incrucisare:" << endl;
		vector<int> crossoverParticipants;
		for (int i = 0; i < population.size(); ++i) {
			double u = uniform(re);
			cout << i + 1 << ":\t" << population[i].GetBinaryValue() << "\tu = " << u << "\t";
			if (u < crossoverProbabilty) {
				crossoverParticipants.push_back(i);
				cout << "< " << crossoverProbabilty << " <- Participa";
			}
			cout << endl;
		}

		cout << endl;
		int n = crossoverParticipants.size();
		for (int i = 0; i < n / 2; ++i) {
			int point = uniformInt(re);

			uniform_int_distribution<int> crom1(0, crossoverParticipants.size() - 1);
			int index1 = crom1(re);
			int c1 = crossoverParticipants[index1];
			crossoverParticipants.erase(crossoverParticipants.begin() + index1);

			uniform_int_distribution<int> crom2(0, crossoverParticipants.size() - 1);
			int index2 = crom2(re);
			int c2 = crossoverParticipants[index2];
			crossoverParticipants.erase(crossoverParticipants.begin() + index2);

			cout << "Recombinare dintre cromozomul " << c1 << " si cromozomul " << c2 << " -- punct " << point << endl;
			cout << "Initial:\t" << population[c1].GetBinaryValue() << "\t" << population[c2].GetBinaryValue() << endl;
			string s1 = population[c1].GetBinaryValue();
			string s2 = population[c2].GetBinaryValue();
			string r1 = population[c2].GetBinaryValue(); r1.erase(r1.begin(), r1.begin() + point);
			s1.replace(s1.begin() + point, s1.end(), r1.c_str());
			string r2 = population[c1].GetBinaryValue(); r2.erase(r2.begin(), r2.begin() + point);
			s2.replace(s2.begin() + point, s2.end(), r2.c_str());
			cout << "Rezultat:\t" << s1 << "\t" << s2 << endl;
		}

		// Mutation phase
		cout << endl << "Faza de mutatie:" << endl;
		for (int i = 0; i < population.size(); ++i) {

			string s = population[i].GetBinaryValue();
			bool modified = false;

			for (int j = 0; j < s.size(); ++j) {
				double u = uniform(re);
				if (u < mutationProbability) {
					modified = true;
					if (s[j] == '0') {
						s[j] = '1';
					}
					else {
						s[j] = '0';
					}
				}
			}

			population[i].ChangeBinary(s);

			if (modified) {
				cout << "Cromozomul " << i << " a suferit mutatii" << endl;
			}
		}

		cout << endl << "Dupa mutatie:" << endl;
		for (int i = 0; i < population.size(); ++i) {
			cout << i + 1 << ":\t" << population[i].GetBinaryValue() << "\tx = " << population[i].GetNumericalValue() << "\tf = " << function(population[i].GetNumericalValue()) << endl;
			
		}

		double max = INT_MIN;
		// Finding the maximum value from this iteration
		for (int i = 0; i < population.size(); ++i) {
			if (function(population[i].GetNumericalValue()) >= max) {
				max = function(population[i].GetNumericalValue());
			}
		}
		summary.push_back(max);
	}

	// Printing all the maximal values from each round
	cout << endl << "Sumar:" << endl << endl;
	for (int i = 0; i < numberOfStages; ++i) {
		cout << "Round " << i + 1 << ": " << summary[i] << endl;
	}
}
