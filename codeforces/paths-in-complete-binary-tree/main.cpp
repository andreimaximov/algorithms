#include <bits/stdc++.h>

using namespace std;  // NOLINT

//
// Calculates the root node of a tree with n nodes.
//
int64_t root(int64_t n) {
  return (n + 1) / 2;
}

//
// Calculates the parent of node u. Returns u if u is the root of a tree with
// n nodes.
//
int64_t parent(int64_t u, int64_t n) {
  // Return u if it is the root.
  if (u == root(n)) {
    return root(n);
  }

  // Traverse up left edge of the tree tracking the size of the tree rooted
  // at p.
  int64_t p = 1;
  int64_t s = 1;

  while (p <= u) {
    p *= 2;
    s  = s * 2 + 1;
  }

  // p is always the parent of v and s is now the size of the tree rooted at v.
  int64_t v = p / 2;
  s = s / 2;

  // Search for u in the tree rooted at v.
  while (v != u) {
    // v is going down a level so update the parent to v.
    p = v;

    if (v < u) {  // Go left
      v = v + s / 4 + 1;
      s = s / 2;
    } else if (v > u) {  // Go right
      v = v - s / 4 - 1;
      s = s / 2;
    }
  }

  return p;
}

//
// Calculates the size of the tree rooted at node u.
//
int64_t size(int64_t u, int64_t n) {
  if (u == root(n)) {
    return n;
  }

  int64_t p = parent(u, n);
  return (abs(p - u) - 1) * 2 + 1;
}

//
// Returns the left child of node u or u itself if u is a leaf.
//
int64_t left(int64_t u, int64_t n) {
  int64_t s = size(u, n);
  if (s == 1) {
    return u;
  }
  return u - s / 4 - 1;
}

//
// Returns the right child of node u or u itself if u is a leaf.
//
int64_t right(int64_t u, int64_t n) {
  int64_t s = size(u, n);
  if (s == 1) {
    return u;
  }
  return u + s / 4 + 1;
}

int main() {
  int64_t n, q;
  cin >> n >> q;

  for (int64_t i = 0; i < q; i++) {
    int64_t u;
    cin >> u;

    string s;
    cin >> s;

    // Create a stack that keeps track of the path from the current node to
    // the root.
    vector<int64_t> stack;
    stack.push_back(u);

    while (stack.back() != root(n)) {
      stack.push_back(parent(stack.back(), n));
    }

    reverse(stack.begin(), stack.end());

    // Update current node keeping track of history.
    for (char c : s) {
      if (c == 'U' && stack.back() != root(n)) {
        stack.pop_back();
      } else if (c == 'L') {
        int64_t v = left(stack.back(), n);
        if (v != stack.back()) {  // Go left only if current node is not leaf!
          stack.push_back(v);
        }
      } else if (c == 'R') {
        int64_t v = right(stack.back(), n);
        if (v != stack.back()) {  // Go right only if current node is not leaf!
          stack.push_back(v);
        }
      }
    }

    cout << stack.back() << endl;
  }

  return 0;
}

