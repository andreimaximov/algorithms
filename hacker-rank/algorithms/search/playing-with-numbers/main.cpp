#include <iostream>
#include <vector>

#define MIN -2000
#define MAX 2000
#define ORIGIN 2001  // Location of 0 in the index
#define SIZE 4003  // MAX - MIN + 2 + 1

struct IndexVector {
  int64_t left = 0;
  int64_t here = 0;
  int64_t right = 0;
};

struct IndexMeta {
  IndexVector sum;
  IndexVector count;
};

class QueryService {
 private:
  typedef std::vector<IndexMeta> Index;

  int64_t position;

  Index index;

  QueryService(int64_t origin, int64_t size) : position(origin), index(size) {
  }

  static void buildleft(Index& idx) { // NOLINT
    idx[0].count.left = 0;
    idx[0].sum.left = 0;
    for (int i = 1; i < idx.size(); ++i) {
      idx[i].count.left = idx[i - 1].count.left + idx[i - 1].count.here;
      idx[i].sum.left = idx[i - 1].sum.left + idx[i].count.left;
    }
  }

  static void buildright(Index& idx) { // NOLINT
    idx[idx.size() - 1].count.right = 0;
    idx[idx.size() - 1].sum.right = 0;
    for (int i = idx.size() - 2; i >= 0; --i) {
      idx[i].count.right = idx[i + 1].count.right + idx[i + 1].count.here;
      idx[i].sum.right = idx[i + 1].sum.right + idx[i].count.right;
    }
  }

  static void buildindex(Index& idx) { // NOLINT
    buildleft(idx);
    buildright(idx);
    for (size_t i = 0; i < idx.size(); ++i) {
      idx[i].sum.here = idx[i].sum.left + idx[i].sum.right;
    }
  }

 public:
  int64_t query(int x) {
    this->position -= x;
    if (this->position < 0) {
      int64_t offset = this->index[0].count.right * - this->position;
      return this->index[0].sum.right + offset;
    } else if (this->position > this->index.size() - 1) {
      int64_t offset = this->position - this->index.size() + 1;
      size_t last = this->index.size() - 1;
      return this->index[last].sum.left + this->index[last].count.left * offset;
    }
    return this->index[this->position].sum.here;
  }

  static QueryService load(std::istream& in, int N) { // NOLINT
    QueryService service(ORIGIN, SIZE);
    int i;
    while (N-- > 0) {
      in >> i;
      i += ORIGIN;
      service.index[i].count.here++;
    }
    buildindex(service.index);
    return service;
  }
};

int main() {
  int N, Q, x;
  std::cin >> N;
  QueryService service = QueryService::load(std::cin, N);
  std::cin >> Q;
  while (Q-- > 0) {
    std::cin >> x;
    std::cout << service.query(x) << std::endl;
  }
  return 0;
}
