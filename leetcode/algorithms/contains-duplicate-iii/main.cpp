#include <algorithm>
#include <vector>
#include <map>

class Solution {
 public:
  //
  // Checks if there are at least two indexes i and j such that abs(i - j) <=
  // abs(k) and abs(nums[i], [j]) <= t.
  //
  bool containsNearbyAlmostDuplicate(const std::vector<int> nums,
                                     int k, int t) {
    // Absolute difference < 0 is not possible. Also, no way to have a pair of
    // (i, j) where i != j if i - j == 0.
    if (t < 0 || k == 0) {
      return false;
    }

    // For ease of index comparison.
    k = abs(k);

    // Track last k elements and number of occurences in sorted order.
    std::map<int, int> history;

    int size = nums.size();
    for (int i = 0; i < size; ++i) {
      int n = nums[i];

      // Get smallest in range element while accounting for underflow.
      int lo = n - t;
      if (lo > n) {
        lo = std::numeric_limits<int>::min();
      }

      // Get largest in range element while accounting for overflow.
      int hi = n + t;
      if (hi < n) {
        hi = std::numeric_limits<int>::max();
      }

      // Find first element >= lo.
      auto firstGTElo = history.lower_bound(lo);

      // Check if it is in bounds.
      if (firstGTElo != history.end() && firstGTElo->first <= hi) {
        return true;
      }

      // Update count of this element.
      history[n]++;

      // Trim trailing elements.
      if (i >= k) {
        int toRemove = nums[i - k];
        history[toRemove]--;
        if (history[toRemove] <= 0) {
          history.erase(toRemove);
        }
      }
    }

    return false;
  }
};


//
// Delete before submitting to LeetCode.
//
int main() {
}
