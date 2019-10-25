#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Event {
private:
	int id, profit, deadline;
	static int idx;
public:
	Event(int profit, int deadline) {
		// Increasing the id
		idx++;
		id = idx;
		
		this->profit = profit;
		this->deadline = deadline;
	}

	int getId() {
		return this->id;
	}

	int getProfit() {
		return this->profit;
	}

	int getDeadline() {
		return this->deadline;
	}

	static bool compare(Event a, Event b) {
		return a.profit > b.profit;
	}
};
int Event::idx = 0;

class Scheduler {
private:
	vector<Event> events;
	vector<int> intervals;

	int Find(int deadline) {
		if (intervals[deadline] == deadline) {
			return deadline;
		}
		else return intervals[deadline] = Find(intervals[deadline]); // when a new node is introduced all the other nodes become his children
	}

	void Union(int a, int b) {
		intervals[a] = b;
	}

public:
	Scheduler(const char* file) {
		ifstream f(file);

		if (f.is_open()) {
			int n; f >> n; // Number of events
			for (int i = 0; i < n; ++i) {
				int profit, deadline;
				f >> profit >> deadline;
				Event e(profit, deadline);
				events.push_back(e);
			}
		}
		else {
			events = vector<Event>();
		}

		// Sorting events by profit
		sort(events.begin(), events.end(), Event::compare);
	}

	void printEvents() {
		for (int i = 0; i < events.size(); i++)
		{
			cout << "Event: " << events[i].getId() << "\tProfit: " << events[i].getProfit() << "\tDeadline: " << events[i].getDeadline() << endl;
		}
		cout << endl;
	}

	void printSchedule() {
		// Preparing disjoint sets
		intervals.assign(events.size() + 1, -1);
		for (int i = 0; i < intervals.size(); ++i) {
			intervals[i] = i;
		}

		for (int i = 0; i < events.size(); i++)
		{
			int response = Find(events[i].getDeadline()); // find the next furthest available time slot
			if (response != 0) {
				Union(response, response - 1); // Telling all other events that the time slot [response-1, response] is scheduled
				cout << "Event: " << events[i].getId() << " scheduled from " << response << " to " << response - 1 << endl;
			}
		}
		cout << endl;
	}
};

int main()
{
	Scheduler scheduler("plan2.txt");
	scheduler.printEvents();
	scheduler.printSchedule();
}