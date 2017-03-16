#include <bits/stdc++.h>

using namespace std;  // NOLINT

//
// Runs DFS to create a Euler Tour of the graph G starting at vertex u.
//
void dfs(const vector<vector<int>>& graph,  // Graph as an adjacency list
         vector<bool>& visited,             // Visited vertices
         vector<int>& tour,                 // Ordered list of visited vertices
         int u) {                           // Vertex where to start DFS
  assert(!visited[u]);

  visited[u] = true;
  tour.push_back(u);

  for (int v : graph[u]) {
    if (!visited[v]) {
      dfs(graph, visited, tour, v);
      // Come back to parent before visiting an adjacent sibling of v or
      // parent of u!
      tour.push_back(u);
    }
  }
}

int main() {
  int n, m, k, x, y;
  cin >> n >> m >> k;

  // Load graph into adjacency list
  vector<vector<int>> graph(n);
  for (int i = 0; i < m; i++) {
    cin >> x >> y;
    x--; y--;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  // Create a Euler Tour which will have no more than 2 * n - 1 vertices
  vector<bool> visited(n, false);
  vector<int> tour;
  dfs(graph, visited, tour, 0);

  // Calculate the max number of vertices each clone can visit
  int range = ((2 * n) % k == 0) ? (2 * n) / k : (2 * n) / k + 1;
  int total = tour.size();

  for (int i = 0; i < k; i++) {
    int start = i * range;
    if (start >= total) {
      // We've already visited all vertices with other clones!
      cout << "1 1" << endl;
    } else {
      // Visit up to the next range vertices via clone i
      int end = min(start + range, total);
      cout << (end - start);
      for (int j = start; j < end; j++) {
        cout << " " << tour[j] + 1;
      }
      cout << endl;
    }
  }

  return 0;
}

