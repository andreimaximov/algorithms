#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> matrix;

matrix build(size_t N, size_t M) {
  matrix graph(N, std::vector<int>(N, -1));
  uint32_t x, y, r;
  while (M-- > 0) {
    std::cin >> x >> y >> r;
    graph[--x][--y] = r;
  }
  while (N-- > 0) {
    graph[N][N] = 0;
  }
  return graph;
}

void floyd_warshall(matrix& graph, size_t N) { // NOLINT
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < N; ++k) {
        if (graph[j][i] == -1 || graph[i][k] == -1) {
          continue;
        }
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
  matrix graph = build(N, M);
  floyd_warshall(graph, N);

  size_t Q;
  int a, b;
  std::cin >> Q;
  while (Q-- > 0) {
    std::cin >> a >> b;
    std::cout << graph[--a][--b] << std::endl;
  }

  return 0;
}
