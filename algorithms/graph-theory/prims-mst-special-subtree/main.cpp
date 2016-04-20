#include <iostream>
#include <vector>
#include <queue>

struct edge {
  int to;  // The vertex this edge is directed at
  int cost;
};

struct vertex {
  std::vector<edge> edges;
};

struct comparator {
  bool operator()(const edge& lhs, const edge& rhs) {
    return lhs.cost > rhs.cost;
  }
};

class subgraph {
 private:
  typedef std::priority_queue<edge, std::vector<edge>, comparator> edgequeue;

  std::vector<bool> visited;

  edgequeue queue;

  void push(const vertex& node) {
    for (const edge& edge : node.edges) {
      if (this->visited[edge.to]) {
        continue;
      }
      this->queue.push(edge);
    }
  }

 public:
  int calculate(const std::vector<vertex>& verticies, int S) {
    int cost = 0;
    this->visited.assign(verticies.size(), false);

    this->queue.emplace(edge {S, 0});
    while (!this->queue.empty()) {
      edge current = this->queue.top();
      this->queue.pop();
      if (this->visited[current.to]) {
        continue;
      }
      this->visited[current.to] = true;
      cost += current.cost;
      this->push(verticies[current.to]);
    }

    this->visited.clear();  // Clear visited vertices
    this->queue = edgequeue();  // Clear the edge queue

    return cost;
  }
};

int main() {
  int N, M, x, y, r, S;
  std::cin >> N >> M;

  std::vector<vertex> verticies(N + 1);
  for (size_t i = 0; i < M; ++i) {
    std::cin >> x >> y >> r;
    verticies[x].edges.emplace_back(edge {y, r});
    verticies[y].edges.emplace_back(edge {x, r});
  }

  subgraph sub;

  std::cin >> S;
  std::cout << sub.calculate(verticies, S) << std::endl;

  return 0;
}
