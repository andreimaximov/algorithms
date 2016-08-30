#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::sort;

class Solution {
 public:
  //
  // The premise of this algorithm is to begin with the empty set and append
  // each number to a copy of each existing set. The issue arises when N[i] and
  // N[i + 1] for any i in (0, len(N) - 2).
  //
  // Define f(a, x) as an operation that returns a copy of each list in a with
  // x appended to the end.
  //
  // The existing subsets S can be viewed as the concatenation of two lists A
  // and B such that S = A + B, B = f(D, N[i]), A = C + D. Since
  // N[i] == N[i + 1] and D is a subset of A, then f(D, N[i]) is a subset of
  // f(A, N[i + 1]). Thus f(A, N[i + 1]) would result in duplicate subsets
  // which we do not want.
  //
  // In simple english terms this means that when we run into two adjacent
  // identical elements, we need to run the copy and append operation only  on
  // the last batch of subsets that were generated.
  //
  vector<vector<int>> subsetsWithDup(const vector<int>& nums) {
    // Sort numbers so that we can easily avoid duplicates later.
    vector<int> copy(nums);
    sort(copy.begin(), copy.end());

    // Initialize subsets with the empty set.
    vector<vector<int>> subsets(1);

    // The index of the set to copy and append the current number to.
    size_t start = 0;

    for (size_t i = 0; i < copy.size(); i++) {
      int current = copy[i];
      size_t n = subsets.size();

      // Append the current number to a copy of each existing subset that will
      // not create duplicate sets.
      for (size_t j = start; j < n; j++) {
        vector<int> copy = subsets[j];
        copy.push_back(current);
        subsets.push_back(std::move(copy));
      }

      if (i < copy.size() - 1 && copy[i] == copy[i + 1]) {
        // On the next iteration append only to elements in the last batch to
        // avoid duplicates.
        start = n;
      } else {
        start = 0;
      }
    }

    return subsets;
  }
};

//
// Delete before submitting to LeetCode.
//
int main() {
  cout << "Please run this solution on LeetCode." << endl;
  cout << "https://leetcode.com/problems/subsets-ii/" << endl;
  return 0;
}
