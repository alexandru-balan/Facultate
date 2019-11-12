#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Job {
private:
	int start, finish, profit;
public:
	Job() {
		start = finish = profit = -1;
	}
	Job(int start, int finish, int profit) {
		this->start = start;
		this->finish = finish;
		this->profit = profit;
	}
	int getStart() {
		return start;
	}
	int getFinish() {
		return finish;
	}
	int getProfit() {
		return profit;
	}
	static bool Compare(Job A, Job B) {
		return A.finish < B.finish;
	}
	friend ostream& operator<<(ostream& o, const Job& J) {
		o << "(" << J.start << ", " << J.finish << ", " << J.profit << ")\n";
		return o;
	}
};

class Scheduler {
private:
	vector<Job> Jobs;
	int binSearch(vector<Job> Jobs, int i) {
		int lower = 0;
		int upper = i - 1;

		while (lower <= upper) {
			int middle = (lower + upper) / 2;

			if (Jobs[middle].getFinish() <= Jobs[i].getStart()) {
				if (Jobs[middle + 1].getFinish() <= Jobs[i].getStart()) {
					lower = middle + 1;
				}
				else {
					return middle;
				}
			}
			else {
				upper = middle - 1;
			}
		}

		return -1; // No previous job is compatible with this one
	}
public:
	Scheduler() {
		Jobs = vector<Job>();
	}
	Scheduler(const char* fileName) {
		Jobs = vector<Job>();

		// Reading jobs from file
		ifstream f(fileName);

		if (f.is_open()) {
			int n; f >> n;

			for (int i = 0; i < n; ++i) {
				int s, fin, p;
				f >> s; f >> fin; f >> p;
				Job newJob(s, fin, p);
				Jobs.push_back(newJob);
			}
		}
	}
	void MakeSchedule() {
		// Sorting by finish time
		sort(Jobs.begin(), Jobs.end(), Job::Compare);

		// We need to store the maximum profit that can be achieved by scheduling jobs form 0 to k, where k = 1,n
		// The Dynamical Programming pradigm is based on storing the result of subproblems which are used to compute other subroblems.
		// This way we avoid re-computing a problem that has already been solved before.

		vector<int> Profits = vector<int>(Jobs.size(),0); // Profits will be stored here
		vector<vector<Job>>BestJobs = vector<vector<Job>>(Jobs.size(),vector<Job>()); // Here we will store the jobs that give the best profits

		// The best schedule that ends with job 0
		Profits[0] = Jobs[0].getProfit();
		BestJobs[0].push_back(Jobs[0]);

		for (int i = 1; i < Jobs.size(); ++i) {
			int nextProfit = Jobs[i].getProfit();
			int compatibleJobIndex = binSearch(Jobs, i);

			if (compatibleJobIndex != -1) {
				nextProfit += Profits[compatibleJobIndex];
			}
			else {
				BestJobs[i].push_back(Jobs[i]);
				Profits[i] = nextProfit;
				continue;
			}

			if (nextProfit > Profits[i-1]) {
				Profits[i] = nextProfit;
				BestJobs[i] = BestJobs[compatibleJobIndex]; BestJobs[i].push_back(Jobs[i]);
			}
			else {
				Profits[i] = Profits[i-1];
				BestJobs[i] = BestJobs[i-1];
			}
		}

		cout << Profits[Jobs.size() - 1]<<endl;
		for (int i = 0; i < BestJobs[Jobs.size() - 1].size(); ++i) {
			cout << BestJobs[Jobs.size() - 1][i];
		}
	}
};

int main()
{
	Scheduler s("date.in");
	s.MakeSchedule();

	return 0;
}