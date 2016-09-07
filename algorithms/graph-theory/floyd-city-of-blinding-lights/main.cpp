#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> matrix;

//
// Builds an adjacency matrix representation of a graph with N vertices. Each
// graph[i][j] is the length of an edge between vertices i and j. Lengths of -1
// indicate there is no edge between two vertices.
//
matrix build_graph(size_t N, size_t M) {
  matrix graph(N, std::vector<int>(N, -1));

  size_t x, y;
  int r;
  while (M-- > 0) {
    std::cin >> x >> y >> r;
    graph[--x][--y] = r;
  }

  // Zero out edges to self.
  for (size_t i = 0; i < N; i++) {
    graph[i][i] = 0;
  }

  return graph;
}

//
// Takes an adjacency matrix graph of distances between vertices and runs Floyd
// Warshall to find the shortest distances between all pairs of vertices.
// Distances of -1 indicate there is no path between a pair of vertices.
//
// See: http://www.cs.cornell.edu/~wdtseng/icpc/notes/graph_part3.pdf
//
void floyd_warshall(matrix& graph, size_t N) { // NOLINT
  // After the n-th iteration of the loop, each graph[j][k] contains the length
  // of the shortest path from j to k through some or none of vertices
  // {0...n - 1}.
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      for (size_t k = 0; k < N; ++k) {
        // Use vertex i as a mid-point between j and k. Check if there even
        // exists a path from j -> i and i -> k.
        if (graph[j][i] == -1 || graph[i][k] == -1) {
          continue;
        }
        // Check if path j -> ? -> i -> ? -> k is shorter than j -> ? -> k.
        int candidate = graph[j][i] + graph[i][k];
        if (candidate < graph[j][k] || graph[j][k] == -1) {
          graph[j][k] = candidate;
        }
      }
    }
  }
}

int main() {
  size_t N, M;
  std::cin >> N >> M;
  matrix graph = build_graph(N, M);
  floyd_warshall(graph, N);

  size_t Q;
  std::cin >> Q;
  while (Q-- > 0) {
    int a, b;
    std::cin >> a >> b;
    std::cout << graph[--a][--b] << std::endl;
  }

  return 0;
}

