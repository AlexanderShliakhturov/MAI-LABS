#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
	int left;
	int right;
	int index;	
};

bool CompareIntervals(const Interval &a, const Interval &b) {
	return a.index < b.index;
}

void FindCoverage(vector<Interval> &intervals, int targetLength) {
	vector<Interval> result;
	Interval initialInterval = {0, 0, -1}; 
	result.push_back(initialInterval);
	
	while (result.back().right < targetLength) {
		int farthestReach = 0;
		int bestIntervalIndex = -1;
		for (int i = 0; i < intervals.size(); ++i) {
			if (intervals[i].left <= result.back().right && intervals[i].right > result.back().right) {
				if (intervals[i].right > farthestReach) {
					farthestReach = intervals[i].right;
					bestIntervalIndex = i;
				}
			}
		}

		if (bestIntervalIndex == -1) {
			cout << "0\n";
			return;
		} else {
			result.push_back(intervals[bestIntervalIndex]);
		}
	}

	sort(result.begin() + 1, result.end(), CompareIntervals);
	cout << result.size() - 1 << '\n';
	for (size_t i = 1; i < result.size(); ++i) {
		cout << result[i].left << " " << result[i].right << '\n';
	}
}

int main() {
	int numIntervals, targetLength;
	cin >> numIntervals;
	vector<Interval> intervals(numIntervals);
	for (int i = 0; i < numIntervals; ++i) {
		intervals[i].index = i;
		cin >> intervals[i].left >> intervals[i].right;
	}
	cin >> targetLength;
	FindCoverage(intervals, targetLength);
	return 0;
}

