#include <cassert>
#include <iostream>
#include <vector>

#define USE_BIT true

#if USE_BIT

//
// Binary Index/Fenwick Tree implementation. See TopCoder article for tutorial.
//
// https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
//
class NumArray {
 private:
  // The underlying BIT.
  std::vector<int> T;

  //
  // Returns the sum of the first i elements of N in O(log |N|) time.
  //
  int query(int i) {
    int s = 0;

    while (i > 0) {
      s += T[i];
      i -= (i & -i);
    }

    return s;
  }

 public:
  explicit NumArray(std::vector<int> N): T(N.size() + 1, 0) {
    for (size_t i = 0; i < N.size(); i++) {
      update(i, N[i]);
    }
  }

  //
  // Updates the value at index i in the array by x in O(log |N|) time.
  //
  void update(int i, int x) {
    int n = static_cast<int>(T.size());

    assert(i >= 0 && i < n - 1);

    int d = x - sumRange(i, i);  // Calculate the change in N[i].
    i++;

    while (i < n) {
      T[i] += d;
      i += (i & -i);
    }
  }

  //
  // Returns sum of N[i...j] in O(log |N|) time.
  //
  int sumRange(int i, int j) {
    int n = static_cast<int>(T.size());

    assert(i >= 0 && i < n - 1);
    assert(j >= 0 && j < n - 1);
    assert(i <= j);

    return query(j + 1) - query(i);
  }
};

#else

//
// Segment Tree implementation. See Top Coder article for tutorial.
//
// https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/#Segment_Trees
//
class NumArray {
 private:
  // The underlying segment tree with T[i] = Sum of elements i node i's range.
  std::vector<int> T;

  // Size of the original array.
  int n;

  //
  // Builds the Segment Tree at node k with sum of range N[lo...hi] and returns
  // the number nodes used in T.
  //
  int build(int k, int lo, int hi, const std::vector<int>& N) {
    if (lo == hi) {
      T[k] = N[lo];
      return k + 1;
    } else {
      int mid = lo + (hi - lo) / 2;
      int nodes = std::max(build(k * 2 + 1, lo, mid, N),
                           build(k * 2 + 2, mid + 1, hi, N));
      T[k] = T[k * 2 + 1] + T[k * 2 + 2];
      return nodes;
    }
  }

  //
  // Returns the sum of the portion of range N[i...j] in node k with range
  // N[lo...hi].
  //
  int query(int k, int lo, int hi, int i, int j) {
    if (lo >= i && hi <= j) {
      return T[k];  // This node partially represents the query range.
    } else if (lo > j || hi < i) {
      return 0;  // This node does not contain the query range.
    }

    int mid = lo + (hi - lo) / 2;
    return query(k * 2 + 1, lo, mid, i, j) +
           query(k * 2 + 2, mid + 1, hi, i, j);
  }

  //
  // Updates index i with value x in node k with range N[lo..hi].
  //
  void update(int k, int lo, int hi, int i, int x) {
    if (i < lo || i > hi) {
      return;  // Index i is not in range of node k!
    } else if (lo == hi) {
      T[k] = x;
    } else {
      int mid = lo + (hi - lo) / 2;
      update(k * 2 + 1, lo, mid, i, x);
      update(k * 2 + 2, mid + 1, hi, i, x);
      T[k] = T[k * 2 + 1] + T[k * 2 + 2];
    }
  }

 public:
  explicit NumArray(std::vector<int> N): n(N.size()) {
    if (N.empty()) return;

    // Calculate the smallest number of leaves in a full binary tree with at
    // least |N| leaves.
    int p = 1;
    while (p < static_cast<int>(N.size())) p *= 2;

    // Build the Segment Tree in O(|N|) time.
    T.resize(p * 2 - 1);
    int nodes = build(0, 0, N.size() - 1, N);
    T.resize(nodes);
  }

  //
  // Updates the value at index i in the array to x in O(log |N|) time.
  //
  void update(int i, int x) {
    assert(i >= 0 && i < n);
    update(0, 0, n - 1, i, x);
  }

  //
  // Returns sum of [i, j] in O(log |N|) time.
  //
  int sumRange(int i, int j) {
    assert(i >= 0 && i < n);
    assert(j >= 0 && j < n);
    assert(i <= j);

    return query(0, 0, n - 1, i, j);
  }
};

#endif

//
// Delete before submitting to LeetCode.
//
int main() {
  std::cout << "Begin tests..." << std::endl;

  NumArray _({});

  NumArray array({1, 2, 3, 4, 5});
  assert(array.sumRange(0, 1) == 3);
  assert(array.sumRange(2, 2) == 3);
  assert(array.sumRange(0, 4) == 15);

  array.update(2, 0);
  assert(array.sumRange(0, 1) == 3);
  assert(array.sumRange(2, 2) == 0);
  assert(array.sumRange(0, 4) == 12);

  array.update(2, 1);
  assert(array.sumRange(0, 1) == 3);
  assert(array.sumRange(2, 2) == 1);
  assert(array.sumRange(0, 4) == 13);

  std::cout << "Tests pass!" << std::endl;
  std::cout << "Please run this solution on LeetCode." << std::endl;
  std::cout << "https://leetcode.com/articles/range-sum-query-mutable/" << std::endl;  // NOLINT
  return 0;
}
