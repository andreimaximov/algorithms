#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution {
 private:
  //
  // Calculates the Kth (0 indexed) permutation of the given set of digits.
  //
  // @see https://discuss.leetcode.com/topic/17348/explain-like-i-m-five-java-solution-in-o-n/2
  //
  // @param current The string to populate starting at index i.
  // @param i       The start index of the current suffix we are working on.
  // @param digits  The set of digits that are available for use. Sorted in
  //                ascending order.
  // @param p       The total count of permutations of the remaining digits.
  // @parma k       The 0-indexed permutation we want to generate.
  //
  void permute(string& current, uint32_t i, vector<uint32_t>& digits, // NOLINT
               uint32_t p, uint32_t k) {
    assert(i < current.size());
    assert(!digits.empty());
    assert(p > 0);
    assert(k >= 0);

    size_t n = current.size();
    size_t m = n - i;  // Size of the suffix current[i:] we are working on.

    // Base case - If this is the last character in the string just use the
    // last available digit.
    if (i == n - 1) {
      current[i] = '0' + digits[0];
      return;
    }

    // Calculate the number of permutations in the last m - 1 digits. Does not
    // include the current index!
    p /= m;

    // Figure out which digit we want to use for the current index i. p is
    // the number of permutation in the last m - 1 digits so we can divide k by
    // p to count how many full permutation sequences in the last m - 1 digits
    // we can skip.
    uint32_t offset =  k / p;

    // Insert the digit into the string and erase it from the set because we
    // can no longer use it.
    current[i] = '0' + digits[offset];
    digits.erase(digits.begin() + offset);

    permute(current, i + 1, digits, p, k % p);
  }

  //
  // Calculates n!. Does not check for overflow.
  //
  inline uint32_t factorial(uint32_t n) {
    assert(n > 0);
    uint32_t f = 1;
    while (n > 1) {
      f *= n;
      n -= 1;
    }
    return f;
  }

 public:
  //
  // Returns the Kth permutation of {1, 2 ... n}.
  //
  string getPermutation(uint32_t n, uint32_t k) {
    assert(n > 0);
    assert(k > 0);
    k -= 1;

    string current(n, '0');

    // Calculate the number of permutations of n digits.
    uint32_t p = factorial(n);
    assert(k < p);

    // Create a set of digits that we can use to generate a permutation.
    vector<uint32_t> digits(n);
    for (uint32_t i = 0; i < n; i++) {
      digits[i] = i + 1;
    }

    permute(current, 0, digits, p, k);
    return current;
  }
};

//
// Delete before submitting to LeetCode.
//
int main() {
  Solution sol;
  assert(sol.getPermutation(3, 5) == "312");

  cout << "Please run this solution on LeetCode." << endl;
  cout << "https://leetcode.com/problems/permutation-sequence/" << endl;
  return 0;
}
