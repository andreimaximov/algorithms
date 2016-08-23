#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <cassert>

using std::vector;
using std::unordered_set;
using std::pair;

typedef pair<int, int> edge;

class Solution {
 private:
  //
  // Builds an adjacency matrix representation of the tree.
  //
  vector<unordered_set<int>> buildAdjacencyMatrix(int n,
                                                  const vector<edge> &edges) {
    vector<unordered_set<int>> a_m(n);
    for (const edge &e : edges) {
      a_m[e.first].insert(e.second);
      a_m[e.second].insert(e.first);
    }
    return a_m;
  }

 public:
  //
  // Finds roots that result in a minimum height tree. There can be at most
  // 2 such trees.
  //
  vector<int> findMinHeightTrees(int n, const vector<edge> &edges) {
    if (n == 0) {
      // No MHT roots available if there is tree is empty.
      return {};
    } else if (n == 1) {
      // Single node tree has only one possible root.
      return {0};
    }

    // Build adjacency matrix.
    vector<unordered_set<int>> a_m = buildAdjacencyMatrix(n, edges);

    // Begin bottom up traversal from leaves.
    vector<int> leaves;
    for (int i = 0; i < n; i++) {
      if (a_m[i].size() == 1) {
        leaves.push_back(i);
      }
    }

    // Continue until we have either one root or two connected roots of equal
    // height left.
    while (n > 2) {
      n -= leaves.size();
      vector<int> next_leaves;
      for (int i : leaves) {
        // Traverse edge to parent and remove to avoid repeated traversal.
        int parent = *a_m[i].begin();
        a_m[parent].erase(i);
        // Queue parent for processing if it is now a leaf.
        if (a_m[parent].size() == 1) {
          next_leaves.push_back(parent);
        }
      }
      leaves = std::move(next_leaves);
    }

    return leaves;
  }
};

void test(int t, int n, const vector<edge> &edges, const vector<int> &roots) {
  Solution sol;
  std::cout << "Running test " << t << std::endl;
  assert(roots == sol.findMinHeightTrees(n, edges));
}

//
// Delete before submitting to LeetCode.
//
int main() {
  test(1, 0, {}, {});
  test(2, 1, {}, {0});
  test(3, 4, {{1, 0}, {1, 2}, {1, 3}}, {1});
  test(4, 6, {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}}, {3, 4});
  return 0;
}
