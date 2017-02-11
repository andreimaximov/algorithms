#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;  // NOLINT

constexpr int MAX_N = 100;

//
// 2 vertices for each original node + supersource + supersink
//
constexpr int MAX_G_V = MAX_N * 2 + 2;

int G[MAX_G_V][MAX_G_V] = {{0}};

int Gr[MAX_G_V][MAX_G_V] = {{0}};

//
// The vertex of u in the graph representing u as a root with up to T units
// of incoming flow flowing to children.
//
int root(int u) {
  return u * 2 + 2;
}

//
// The vertex of u in the graph reprsenting u as a child with flow incoming
// from a root.
//
int child(int u) {
  return u * 2 + 3;
}

//
// Returns the shortest augmentation path in the residual graph from u to v. m
// is the number of vertices in the graph.
//
stack<int> find_path(int u, int v, int m) {
  // Track u for each v where (u -> v) is the edge traversed when v was first
  // discovered.
  vector<int> parents(m, -1);
  parents[u] = u;

  queue<int> bfs;
  bfs.push(u);

  while (!bfs.empty()) {
    int x = bfs.front();
    bfs.pop();

    if (x == v) {
      break;
    }

    // Traverse neighbors
    for (int y = 0; y < m; y++) {
      if (Gr[x][y] > 0 && parents[y] == -1) {
        parents[y] = x;
        bfs.push(y);

        if (y == v) {
          break;
        }
      }
    }
  }

  // Check if no agumentation path exists
  if (parents[v] == -1) {
    return stack<int>();
  }

  // Store path u -> v by traversing up from parent of v
  stack<int> path;
  int x = v;

  while (x != u) {
    path.push(x);
    x = parents[x];
  }
  path.push(u);

  return path;
}

//
// Calculates max flow from u to v using Edmond-Karp. n is the number of nodes
// in the original graph and m is the number of vertices in the transformed
// graph.
//
int max_flow(int u, int v, int n, int m) {
  stack<int> path = find_path(u, v, m);

  // Apply augmenting paths until none are left
  while (!path.empty()) {
    int x = path.top();
    path.pop();

    // Apply each edge along augmenting path
    while (!path.empty()) {
      int y = path.top();
      path.pop();

      Gr[x][y]--;
      Gr[y][x]++;

      x = y;
    }

    path = find_path(u, v, m);
  }

  // Calculate flow exiting the source
  int flow = 0;

  for (int i = 0; i < n; i++) {
    flow += Gr[root(i)][0];
  }

  return flow;
}

int main() {
  int C, N, T, M, u, v;
  cin >> C;

  for (int i = 0; i < C; i++) {
    cin >> N >> T >> M;

    // Clear graph
    memset(G, 0, sizeof(G));

    // Build graph
    for (int j = 0; j < M; j++) {
      cin >> u >> v;
      u--; v--;
      G[root(u)][child(v)] = 1;
      G[root(v)][child(u)] = 1;
    }

    // Create edges from source(u) -> in(u) and in(u) -> out(u)
    for (int u = 0; u < N; u++) {
      G[0][root(u)] = T;
      G[child(u)][1] = 1;
    }

    // Setup residual graph
    memcpy(Gr, G, sizeof(G));

    // Calculate max flow from super source to super sink
    cout << max_flow(0, 1, N, N * 2 + 2) << endl;
  }

  return 0;
}

