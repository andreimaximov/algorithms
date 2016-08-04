#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

//
// Union-find data structure that partitions elements into disjoint sets.
//
class disjoint_sets {
 private:
  struct set {
    int parent = -1;

    size_t size = 1;
  };

  mutable std::vector<set> nodes;

 public:
  explicit disjoint_sets(size_t size): nodes(size) {
  }

  //
  // Returns the set ID that the specified node belongs to.
  //
  size_t find(size_t node) const {
    if (nodes[node].parent == -1) {
      return node;
    }
    nodes[node].parent = find(nodes[node].parent);
    return nodes[node].parent;
  }

  //
  // Merge nodes a and b into the same set using set size heuristic. Returns
  // the new set ID.
  //
  size_t merge(size_t a, size_t b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      return a;  // Already members of same set.
    } else if (nodes[b].size > nodes[a].size) {
      return merge(b, a);
    }
    nodes[b].parent = a;
    nodes[a].size += nodes[b].size;
    return a;
  }
};

//
// Represents a weighted edge in the graph.
//
struct w_edge {
  size_t lhs;

  size_t rhs;

  int32_t weight;
};

uint32_t kruskal(size_t N, const std::vector<w_edge> &edges) {
  uint32_t weight = 0;

  size_t E = 0;  // Tracks the number of edges in the MST for far. We should get
                 // |V| - 1 edges in a complete MST.

  disjoint_sets djs(N);
  for (auto it = edges.begin(); it != edges.end() && E < N - 1; it++) {
    // Ignore this edge if it creates a cycle.
    if (djs.find(it->lhs) == djs.find(it->rhs)) {
      continue;
    }

    // Add this edge to the MST if it creates two disjoint forests.
    djs.merge(it->lhs, it->rhs);
    weight += it->weight;
    E++;
  }

  return weight;
}

int main() {
  size_t N, M;
  std::cin >> N >> M;

  // Load edges and sort by weight
  std::vector<w_edge> edges(M);
  for (size_t i = 0; i < M; i++) {
    std::cin >> edges[i].lhs >> edges[i].rhs >> edges[i].weight;
  }
  std::sort(edges.begin(), edges.end(), [](const w_edge &a, const w_edge &b) {
    return a.weight < b.weight;
  });

  // Run Kruskal's algorithm.
  std::cout << kruskal(N, edges) << std::endl;
  return 0;
}
