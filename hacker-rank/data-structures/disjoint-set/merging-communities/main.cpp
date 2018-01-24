#include <iostream>
#include <sstream>
#include <vector>
#include <string>

//
// DisjointSets class is an efficient implementation of a union-find data
// structure that tracks a collection of elements partitioned into disjoint
// sets.
//
// Path compression is used to improve merge and find performance.
//
class DisjointSets {
 private:
  struct Set {
    int parent = -1;

    size_t size = 1;
  };

  std::vector<Set> objects;

 public:
  explicit DisjointSets(size_t n) : objects(n) {
  }

  //
  // Merges the two sets l and r belong to. This is a no-op if l and r are
  // already part of the same set. Otherwise, the set with elements becomes a
  // child of the larger set.
  //
  // Returns the root set of the merge operation.
  //
  size_t merge(size_t l, size_t r) {
    l = find(l);
    r = find(r);
    if (l == r) {
      return l;
    } else if (objects[l].size < objects[r].size) {
        return merge(r, l);
    }
    objects[r].parent = l;
    objects[l].size += objects[r].size;
    return l;
  }

  //
  // Finds the root of the set i is in while performing path compression.
  //
  size_t find(size_t i) {
    if (objects[i].parent == -1) {
      return i;
    }
    objects[i].parent = find(objects[i].parent);
    return objects[i].parent;
  }

  //
  // Returns the size of the set i belongs to.
  //
  size_t size(size_t i) {
    return objects[find(i)].size;
  }
};

int main() {
  size_t N, Q;
  std::cin >> N >> Q;

  // Ignore until EOL
  std::string line;
  std::getline(std::cin, line);

  DisjointSets ds(N);

  // Process each query...
  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    char type;
    ss >> type;
    size_t I, J;
    ss >> I >> J;
    I--; J--;
    switch (type) {
      case 'M':
        ds.merge(I, J);
        break;
      case 'Q':
        std::cout << ds.size(I) << std::endl;
        break;
      default:
        std::cerr << "Invalid query " << type << "!" << std::endl;
    }
  }
}
