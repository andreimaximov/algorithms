#include <bits/stdc++.h>

using namespace std;  // NOLINT

/**
 * ============================================================
 *                          CONSTANTS
 * ============================================================
 */

/** Max number of nodes in the tree */
constexpr int MAX_N = 100000;

/** Max height of tree after Centroid Decomposition */
constexpr int MAX_LOG_N = 20;

/**
 * ============================================================
 *                       GLOBAL VARIABLES
 * ============================================================
 */

/** Number of nodes in the tree */
int N;

/** TREE[u] is the set of nodes u has an edge to */
set<int> TREE[MAX_N];

/** DP[u][i] is the 2^ith ancestor of node u in the original tree */
int DP[MAX_N][MAX_LOG_N];

/** LEVEL[u] is the depth of node u from root (0) at depth 0 */
int LEVEL[MAX_N];

/** SIZE[u] is the size of the sub-tree at node u during decomposition */
int SIZE[MAX_N];

/** PARENT[u] is the parent of node u in the decomposed tree */
int PARENT[MAX_N];

/** DIST[u] is the distance to the closest red node */
int DIST[MAX_N];

/**
 * ============================================================
 *                        IMPLEMENTATION
 * ============================================================
 */

/**
 * Fills out the LEVEL table and DP[*][0] in O(n) time via DFS.
 */
void levels(int u, int parent, int level) {
  LEVEL[u] = level;
  DP[u][0] = parent;

  for (int v : TREE[u]) {
    if (v != parent) {
      levels(v, u, level + 1);
    }
  }
}

/**
 * Fills out the DP table fin O(n logn) time.
 */
void preprocess() {
  levels(0, -1, 0);

  for (int i = 1; i < ceil(log2(N)) + 1; i++) {
    for (int u = 0; u < N; u++) {
      int v = DP[u][i - 1];
      DP[u][i] = (v != -1) ? DP[v][i - 1] : -1;
    }
  }
}

/**
 * Returns the LCA of nodes u and v in O(log n) time from the original tree.
 *
 * See tutorial here:
 * https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/
 */
int lca(int u, int v) {
  if (u == v) {
    return u;
  }

  // Check if u and v are at the same level in the original tree - NOT the
  // decomposed tree. If u and v are not at the same level make sure u is the
  // lower/deeper of the two for ease of implementation.
  if (LEVEL[u] < LEVEL[v]) {
    return lca(v, u);
  }

  // Pull node u up to the same level as node v so we can binary search in
  // the next section.
  int i = ceil(log2(N)) + 1;
  while (LEVEL[u] > LEVEL[v]) {
    if (DP[u][i] != -1 && LEVEL[DP[u][i]] >= LEVEL[v]) {
      u = DP[u][i];
    }
    i--;
  }

  // Sanity check...
  assert(LEVEL[u] == LEVEL[v]);

  if (u == v) {
    return u;
  }

  // Now binary search for LCA!
  int j = ceil(log2(N)) + 1;
  while (j >= 0) {
    if (DP[u][j] != -1 && DP[u][j] != DP[v][j]) {
      u = DP[u][j];
      v = DP[v][j];
    }
    j--;
  }

  return DP[u][0];
}

/**
 * Calculates the distnace between nodes u and v from the original tree in
 * O(log n) time.
 */
int dist(int u, int v) {
  return LEVEL[u] + LEVEL[v] - 2 * LEVEL[lca(u, v)];
}

/**
 * Calculates the size of the tree rooted at node u, and all of its sub-trees,
 * storing the result in the SIZE table.
 */
int size(int u, int p) {
  SIZE[u] = 1;

  for (int v : TREE[u]) {
    if (v != p) {
      SIZE[u] += size(v, u);
    }
  }

  return SIZE[u];
}

/**
 * Finds the centroid of the tree with n nodes rooted at node u without
 * backtracking back through node p.
 */
int centroid(int u, int p, int n) {
  for (int v : TREE[u]) {
    if (v != p && SIZE[v] > n / 2) {
      return centroid(v, u, n);
    }
  }

  return u;
}

/**
 * Performs Centroid Decomposition on the original tree, populating table
 * PARENT. The TREE table is erased after this operation. See the following
 * article for an explanation of Centroid Decomposition.
 *
 * https://threads-iiith.quora.com/Centroid-Decomposition-of-a-Tree
 */
void decompose(int u, int p) {
  // Find centroid and link to parent.
  size(u, -1);
  int c = centroid(u, -1, SIZE[u]);
  PARENT[c] = p;

  /// Recurse...
  for (int v : TREE[c]) {
    TREE[v].erase(c);
    decompose(v, c);
  }

  // Clean up and done!
  TREE[c].clear();
}

/**
 * ============================================================
 *                             API
 * ============================================================
 */

void update(int u) {
  int a = u;

  // Update all ancestors in decomposed tree.
  while (a != -1) {
    DIST[a] = min(DIST[a], dist(u, a));
    a = PARENT[a];
  }
}

int query(int u) {
  int a = u;
  int closest = numeric_limits<int>::max();

  // Query all ancestors in decomposed tree.
  while (a != -1) {
    closest = min(closest, dist(u, a) + DIST[a]);
    a = PARENT[a];
  }

  return closest;
}

int main() {
  int m;
  cin >> N >> m;

  for (int i = 0; i < N- 1; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    TREE[a].insert(b);
    TREE[b].insert(a);
  }

  preprocess();
  decompose(0, -1);

  // Fill in distances before allowing updates/queries. Use a large value to
  // represent "infinite" distance but not large enough to overflow during
  // addition with real distances.
  fill(&DIST[0],
       &DIST[0] + sizeof(DIST) / sizeof(DIST[0]),
       numeric_limits<int>::max() / 2);

  update(0);

  for (int i = 0; i < m; i++) {
    int t, v;
    cin >> t >> v;
    v--;

    switch (t) {
      case 1: update(v); break;
      case 2: cout << query(v) << endl; break;
    }
  }

  return 0;
}

