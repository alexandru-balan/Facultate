#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Job {
private:
	int profit, deadline, time, id;
	static int idx;
public:
	Job() {
		idx++;
		id = idx;
		profit = deadline = time = -1;
	}
	Job(int profit, int deadline, int time) {
		idx++;
		id = idx;
		this->profit = profit;
		this->deadline = deadline;
		this->time = time;
	}
	int getProfit() {
		return profit;
	}
	int getDeadline() {
		return deadline;
	}
	int getTime() {
		return time;
	}
	int getId() {
		return id;
	}

	static bool Compare(Job A, Job B) {
		return A.deadline < B.deadline;
	}
	friend ostream& operator<< (ostream& o, const Job& J) {
		o << "(" << J.profit << ", " << J.deadline << ", " << J.time << ")\n";
		return o;
	}
};
int Job::idx = -1;

class Scheduler {
private:
	vector<Job> Jobs;
public:
	Scheduler() {
		Jobs = vector<Job>();
	}
	Scheduler(const char* fileName) {
		Jobs = vector<Job>();
		ifstream f(fileName);

		// Fake job
		Job job;
		Jobs.push_back(job);

		if (f.is_open()) {
			int n; f >> n;
			for (int i = 0; i < n; ++i) {
				int profit, deadline, time;
				f >> profit; f >> deadline; f >> time;
				Job newJob(profit, deadline, time);
				Jobs.push_back(newJob);
			}
		}
	}
	void MakeSchedule() {
		// Sorting the jobs increasingly by deadline
		sort(Jobs.begin(), Jobs.end(), Job::Compare);

		/*
		We need a structure that can hold the maximum profit we can achieve
		with some jobs in interval 0 to i as well as the maximum deadline by which this profit is made
		*/
		vector<vector<int>> BestJobs = vector<vector<int>>(Jobs.size());
		for (int i = 0; i < BestJobs.size(); ++i) {
			BestJobs[i].assign(Jobs.back().getDeadline(), 0);
		}
		
		for (int i = 1; i < Jobs.size(); i++) {
			for (int j = 0; j < Jobs.back().getDeadline(); ++j) {
				int possibleTime = min(j, Jobs[i].getDeadline()) - Jobs[i].getTime();
				if (possibleTime < 0) {
					BestJobs[i][j] = BestJobs[i - 1][j];
				}
				else {
					BestJobs[i][j] = max(BestJobs[i - 1][j], Jobs[i].getProfit() + BestJobs[i - 1][possibleTime]);
				}
			}
		}

		cout << "Profit maxim: " << BestJobs[Jobs.size()-1][Jobs.back().getDeadline()-1] << endl;

		int m = Jobs.size() - 1; int n = Jobs.back().getDeadline() - 1;

		while (m)
		{
			if (BestJobs[m][n] == BestJobs[m - 1][n]) {
				m--;
				continue;
			}
			else {
				n = min(n, Jobs[m].getDeadline()) - Jobs[m].getTime();
				cout << Jobs[m].getId() << " ";
				m--;
				continue;
			}
		}
	}
};

int main()
{
	Scheduler scheduler("data.in");
	scheduler.MakeSchedule();

	return 0;
}