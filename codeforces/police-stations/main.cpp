#include <bits/stdc++.h>

using namespace std;  // NOLINT

//
// Runs BFS on all frontiers F until all cities have been visited. See comments
// in main(...) for description of V, F, T, and E.
//
void bfs(vector<int>& V,
         vector<vector<int>>& F,
         vector<vector<pair<int, int>>>& T,
         unordered_set<int>& E) {
  bool empty = false;

  // Loop until frontier's are exhausted.
  while (!empty) {
    empty = true;

    for (size_t i = 0; i < F.size(); i++) {
      vector<int> f = std::move(F[i]);
      F[i].clear();

      // Loop through each city in the frontier.
      for (int u : f) {
        // Loop through all edges exiting city u.
        for (auto e : T[u]) {
          int v = e.first;
          int idx = e.second;

          // If the neighbor v of u has not been visited, associate it with the
          // same police station city as u. Otherwise if v is already
          // associated with a different police station that is the same or
          // closer distance to v as the police station of u is to v, delete
          // the road between u and v.
          if (V[v] == -1) {
            V[v] = V[u];
            F[i].push_back(v);
          } else if (V[v] != V[u]) {
            E.insert(idx);  // Delete road!
          }
        }
      }

      // Ensure empty = false if at least one frontier still has cities to
      // visit.
      empty = empty && F[i].empty();
    }
  }
}

int main() {
  int n, k, d;
  cin >> n >> k >> d;

  // BFS frontier starting at each city with a police station.
  vector<vector<int>> F;

  // Map of sub-tree ID's that each city belongs to. Also corresponds to the
  // nearest city with a police station.
  vector<int> V(n, -1);

  // Adjacency list representation of tree of (to-node, edge-index) pairs.
  vector<vector<pair<int, int>>> T(n);

  // Parse all cities with a police station and initialize BFS from each one.
  for (int i = 0; i < k; i++) {
    int p;
    cin >> p;
    p--;
    F.push_back({p});  // BFS frontier starts from police city
    V[p] = p;          // Don't forget to set the sub-tree ID of this city
  }

  // Load tree edges.
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    T[u].push_back(make_pair(v, i));
    T[v].push_back(make_pair(u, i));
  }

  // BFS to collect edges we can delete.
  unordered_set<int> E;
  bfs(V, F, T, E);
  cout << E.size() << endl;

  for (int e : E) {
    cout << e + 1 << " ";
  }
  cout << endl;

  return 0;
}

