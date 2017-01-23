#include <bits/stdc++.h>

using namespace std;  // NOLINT

//
// Represents a node in the tree.
//
struct node {
  int weight;

  vector<int> edges;
};

//
// Represents an edge from x to y with weight w and strength p.
//
struct edge {
  int x;

  int y;

  int w;

  int p;
};

//
// Parses an edge from the istream.
//
istream& operator>>(istream& is, edge& e) {
  is >> e.x >> e.y >> e.w >> e.p;
  e.x--;
  e.y--;
  return is;
}

//
// Writes an edge to the ostream.
//
ostream& operator<<(ostream& os, const edge& e) {
  return os << e.x + 1 << " " << e.y + 1 << " " << e.w << " " << e.p;
}

//
// Lower the weight of the tree as much as possible while fixing it using
// DFS. Returns false if the tree cannot be fixed and true otherwise.
//
bool lower(vector<node>& nodes, vector<edge>& edges, int i) {
  node& n = nodes[i];
  n.weight = 0;

  if (n.edges.empty()) {
    return true;
  }

  for (int j : n.edges) {
    edge& e = edges[j];
    node& child = nodes[e.y];

    if (!lower(nodes, edges, e.y) || e.p < child.weight) {
      return false;
    }

    // Now that the child this edge is connected to has been lowered, lower
    // the weight of the edge as much as possible.
    int cut = min(e.w - 1, e.p - child.weight);
    e.w -= cut;
    e.p -= cut;
    n.weight += e.w + child.weight;
  }

  return true;
}

//
// Raises the weight of the tree up to w_upper weight while keeping it fixed.
// We do this by processing each (edge, child) pair of the current node by
// first increasing the weight of the edge as much as possible and then using
// that to determine an upper bound for the recursive procedur on the child.
//
void raise(vector<node>& nodes,
           vector<edge>& edges,
           const vector<edge>& original,
           int i,
           int w_upper) {
  assert(w_upper >= 0);

  node& n = nodes[i];
  if (n.edges.empty() || n.weight == w_upper) {
    // No way to increase weight or upper weight bound has been met.
    return;
  }

  for (int j : n.edges) {
    edge& e = edges[j];
    node& child = nodes[e.y];

    // Figure out the most we can increase the weight of the edge to the
    // current child by. This is only limited by the original edge weight
    // for edges stemming from the root.
    int e_w_increase = original[j].w - e.w;
    if (i != 0) {
      e_w_increase = min(e_w_increase, w_upper - n.weight);
    }

    // Increase the weight and strength of the edge.
    e.w += e_w_increase;
    e.p += e_w_increase;
    n.weight += e_w_increase;

    // Figure out the upper bound on the weight of the child that would keep
    // the tree fixed. Once again, the root can have unlimited weight in which
    // case w_upper does not apply.
    int c_w_upper = e.p;
    if (i != 0) {
      c_w_upper = min(c_w_upper, w_upper - n.weight + child.weight);
    }

    int c_w_original = child.weight;
    raise(nodes, edges, original, e.y, c_w_upper);

    // Update the weight of this node.
    n.weight += (child.weight - c_w_original);
  }
}

//
// The overall strategy being used for this problem is a 2-phase DFS.
//
// 1) Lower the weight of the tree as much as possible while fixing it. Detect
//    if the tree is not fixable and terminate if needed.
//
// 2) Raise the weight of the lowered and fixed tree as much as possible
//    without exceeding original individual edge weights.
//
int main() {
  int n;
  cin >> n;

  vector<node> nodes(n);
  vector<edge> edges(n - 1);

  for (int i = 0; i < n - 1; i++) {
    cin >> edges[i];
    nodes[edges[i].x].edges.push_back(i);
  }

  vector<edge> original = edges;

  if (!lower(nodes, edges, 0)) {
    cout << -1 << endl;
    return 0;
  }

  raise(nodes, edges, original, 0, numeric_limits<int>::max());
  cout << n << endl;
  for (const edge& e : edges) {
    cout << e << endl;
  }

  return 0;
}

