#include <iostream>
#include <vector>
#include <cassert>

#define ITERATIVE_ALGO true

using std::vector;

class Solution {
 private:
  //
  // Populates order vector starting at the specified index with all integers
  // beginning with current in lexicographical order not greater than n.
  //
  size_t dfs(size_t index, int current, int n, vector<int> &order) { // NOLINT
    if (current > n) {
      return index;
    }
    order[index++] = current;
    for (size_t digit = 0; digit < 10; digit++) {
      int candidate = current * 10 + digit;
      // Not strictly necessary but may help with less unecessary function
      // calls.
      if (candidate > n) {
        continue;
      }
      index = dfs(index, candidate, n, order);
    }
    return index;
  }

  //
  // Returns the next number after the current number is a lexical ordering of
  // 1 ... n. Behavior undefined for the last lexicographically ordered number
  // from 1 to n.
  //
  inline int next(int current, int n) {
    if (current * 10 <= n) {
      // Next number is current followed by a 0.
      return current * 10;
    } else if (current % 10 != 9 && current + 1 <= n) {
      // If current * 10 is out of bounds, next choice is to try current + 1.
      return current + 1;
    } else {
      // This is the most complex case. current is a regex pattern \d*9+. We
      // need to strip trailing 9's and add 1 to prefix \d*.
      while (current % 10 == 9 || current + 1 > n) {
        current = current / 10;
      }
      return current + 1;
    }
  }

 public:
  //
  // Recursive DFS implementation. The idea is that for each "prefix" we can
  // append nothing or any digit in {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}. The
  // lexicographical ordering can be constructed with a pre-order tree
  // traversal like so.
  //
  //    1        2     ...      9
  //   / \      / \            / \                                    // NOLINT
  // 10...19  20...29  ...   90...99
  //
  vector<int> lexicalOrderDfs(int n) {
    size_t i = 0;
    vector<int> order(n);
    for (int digit = 1; digit < 10; digit++) {
      i = dfs(i, digit, n, order);
    }
    return order;
  }

  //
  // Iterative lexical order implementation. See next(int, int) for how
  // ordering is generated.
  //
  vector<int> lexicalOrderIterative(int n) {
    int current = 1;
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
      order[i] = current;
      current = next(current, n);
    }
    return order;
  }

  vector<int> lexicalOrder(int n) {
#ifdef ITERATIVE_ALGO
    return lexicalOrderIterative(n);
#else
    return lexicalOrderDfs(n);
#endif
  }
};

//
// Delete before submitting to LeetCode.
//
int main() {
  Solution sol;
  assert(sol.lexicalOrder(13) ==
      vector<int>({1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9}));
  std::cout << "Tests pass!" << std::endl;
}

