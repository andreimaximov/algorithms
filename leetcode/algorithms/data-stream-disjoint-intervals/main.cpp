#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

//
// Enable this to compile locally.
//
#define IS_LOCAL false

#define DEBUG false

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::lower_bound;
using std::upper_bound;

#if IS_LOCAL

struct Interval {
  int start;

  int end;

  Interval() : start(0), end(0) {
  }

  Interval(int start, int end) : start(start), end(end) {
  }
};

#endif

#if DEBUG

#define LOG printf

#else

#define LOG(...)

#endif

class SummaryRanges {
 private:
  //
  // "Less than" comparator for two intervals. We guarantee that begin <= end
  // for each interval so we can compare the endpoints of two intervals to see
  // if either is entirely before the other. Returns false for overlapping
  // intervals. This is useful because overlapping intervals will be considered
  // equal by the C++ set (BST) and indicate possibility of an interval merge.
  //
  struct LTComparator {
    bool operator()(const Interval& lhs, const Interval& rhs) {
      return lhs.end < rhs.start;
    }
  };

  LTComparator comparator;

  //
  // Keeps intervals ordered from lower to higher ranges. This is possible
  // because the intervals are disjoint and do not overla[]. This allows us
  // to simply compare interval endpoints to order intervals.
  //
  set<Interval, LTComparator> intervals;

 public:
  SummaryRanges() {
  }

  void addNum(const int& value) {
    LOG("Inserting value %d...\n", value);
    Interval candidate(value, value);

    // Check if this value is part of any existing intervals.
    auto it = intervals.find(candidate);
    if (it != intervals.end()) {
      LOG("Using interval [%d, %d] for %d...\n", it->start, it->end, value);
      return;
    }

    // Checks if there is an existing interval that can have its end extended
    // by one to contain the value we are inserting.
    auto lower = lower_bound(intervals.begin(), intervals.end(), candidate,
                             comparator);
    if (lower != intervals.begin()) {
      --lower;
      LOG("Found lower interval [%d, %d]...\n", lower->start, lower->end);
      if (lower->end == value - 1) {
        // We don't actually extend the existing interval. We erase it and
        // merge it into the new interval to contain the one we found. This
        // makes it easier if we also have to merge a higher interval in the
        // next section.
        candidate.start = lower->start;  // start decreases
        intervals.erase(lower);
      }
    }

    // Checks if there is an existing interval that can have its start extended
    // by one to contain the value we are inserting.
    auto upper = upper_bound(intervals.begin(), intervals.end(), candidate,
                             comparator);
    if (upper != intervals.end()) {
      LOG("Found upper inerval [%d, %d]..\n", upper->start, upper->end);
      if (upper->start == value + 1) {
        // Similar to the previous section, erase the lower interval we found
        // and merge it into the new interval.
        candidate.end = upper->end;  // end increases
        intervals.erase(upper);
      }
    }

    intervals.insert(candidate);
  }

  vector<Interval> getIntervals() const {
    return vector<Interval>(intervals.begin(), intervals.end());
  }
};

#if IS_LOCAL

int main() {
  cout << "Please run this solution on LeetCode." << endl;
  cout << "https://leetcode.com/problems/data-stream-as-disjoint-intervals/" << endl; // NOLINT
  return 0;
}

#endif

