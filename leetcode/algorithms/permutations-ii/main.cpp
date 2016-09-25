#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;
using std::reverse;
using std::swap;

class Solution {
 private:
  //
  // Mutates the current permutation to the next one in lexicographical order.
  // Returns a bool indicating if the next permutation is a reset to the
  // initial/lowest lexicographical ordering.
  //
  template<typename T>
  bool next(vector<T>& current) { // NOLINT
    int n = current.size();
    if (n < 2) {
      return false;
    }

    // Find last i such that current[i] < current[i + 1].
    int i = n - 2;
    while (i >= 0 && current[i] >= current[i + 1]) {
      i--;
    }

    // Check if the enture permutation is non-increasing and thus there is no
    // greater lexicographical ordering.
    if (i < 0) {
      reverse(current.begin(), current.end());
      return false;
    }

    // It is now guaranteed that current[i + 1:] is non-increasing. Find last j
    // such that current[i] < current[j] and i < j.
    int j = n - 1;
    while (i < j && current[i] >= current[j]) {
      j--;
    }

    // Swap i and j. Then reverse current[i + 1:].
    swap(current[i], current[j]);
    reverse(current.begin() + i + 1, current.end());
    return true;
  }

 public:
  //
  // Generates a collection of all unqiue permutations of the given values. The
  // values are first sorted and permutation are generated with a next
  // lexicographical ordering algorithm until we loop back to the lowest
  // lexicographical ordering permutation.
  //
  template<typename T>
  vector<vector<T>> permuteUnique(const vector<T>& values) {
    // Create a sorted copy of values which is the initial lowest
    // lexicographical order permutation.
    vector<T> current(values);
    sort(current.begin(), current.end());

    // Tracks if the current permutation is a reset to the lowest
    // lexicographical ordering.
    bool isNext = true;

    vector<vector<T>> permutations;
    while (isNext) {
      permutations.push_back(current);
      isNext = next(current);
    }
    return permutations;
  }
};

//
// Delete before submitting to LeetCode.
//
int main() {
  Solution sol;

  vector<int> input({0, 0, 1});
  auto actual = sol.permuteUnique(input);
  sort(actual.begin(), actual.end());

  vector<vector<int>> expect({{0, 0, 1}, {0, 1, 0}, {1, 0, 0}});
  assert(actual == expect);

  cout << "Please run this solution on LeetCode." << endl;
  cout << "https://leetcode.com/problems/permutations-ii/" << endl;
  return 0;
}
