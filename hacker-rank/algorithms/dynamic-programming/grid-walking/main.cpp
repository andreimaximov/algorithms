#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#define MOD 1000000007

//
// Represents the parsed arguments for each tests case.
//
struct Args {
  size_t N;

  size_t M;

  std::vector<size_t> position;

  std::vector<size_t> dimensions;

  static Args parse(std::istream& in) { // NOLINT
    Args args;
    in >> args.N >> args.M;
    std::copy_n(std::istream_iterator<size_t>(in),
              args.N,
              std::back_inserter(args.position));
    // Transform each Xi in position to be 0 <= Xi < Di
    for (auto it = args.position.begin(); it != args.position.end(); ++it) {
      *it = *it - 1;
    }
    std::copy_n(std::istream_iterator<size_t>(in),
              args.N,
              std::back_inserter(args.dimensions));
    return args;
  }
};


//
// Calculates a^b % p in logarithmic time
//
uint64_t modpow(uint64_t a, uint64_t b, uint64_t p) {
  uint64_t c = 1;
  while (b > 0) {
    if (b % 2 != 0) {
        c = (c * a) % p;
    }
    a = (a * a) % p;
    b /= 2;
  }
  return c;
}

//
// Calculates modular inverse of a mod prime p using Fermat's Little Theorem.
//
uint64_t modinv(uint64_t a, uint64_t p) {
  return modpow(a, p - 2, p);
}

//
// Calculates nCr % p using the following technique.
//
// C(n, r) = n!/((n-r)!r!)
//
// C(n, r) % p = n! % p * (n-r)!^-1 % p * r!^-1 % p
//
// f(n) = n! % p
// g(n) = n!^-1 % p = (f(n) % p)^-1 % p
//
// C(n, r) % p = (f(n) * g(n-r) * g(r)) % p
//
template<typename T>
class nCr {
 private:
  std::vector<T> f;

  std::vector<T> g;

  T p;

  void pre() {
    f[0] = 1;
    for (size_t i = 1; i < f.size(); i++) {
      f[i] = (f[i - 1] * i % p) % p;
    }
    g[0] = 0;
    for (size_t i = 1; i < g.size(); i++) {
      g[i] = modinv(f[i], p);
    }
  }

 public:
  nCr(size_t n, T p) :
    f(n + 1),
    g(n + 1),
    p(p) {
    pre();
  }

  T calculate(size_t n, size_t r) {
    if (r > n) {
      return 0;
    } else if (n == 0 || r == 0 || r == n) {
      return 1;
    }
    return f[n] * g[n - r] % p * g[r] % p;
  }
};

//
// Calculates (a * b) % p
//
template <typename T>
inline T multiply(const T& a, const T& b, const T& p) {
  return ((a % p) * (b % p)) % p;
}

//
// Calculates (a + b) % p
//
template <typename T>
inline T add(const T& a, const T& b, const T& p) {
  return ((a % p) + (b % p)) % p;
}

//
// Calculates the modulo p number of unique paths in a single dimension given a
// starting point and number of steps.
//
class OneDimensionalPaths {
 private:
  typedef std::vector<std::vector<int64_t>> matrix;

  //
  // Cached count % p for all 0 to steps steps
  //
  std::vector<int64_t> counts;

  //
  // The size of this dimension
  //
  size_t size;

  //
  // Prime number used to compute modulo count
  //
  int64_t p;

  //
  // Calculates the modulo p of the number of unique paths with steps number of
  // steps in this dimension starting at the specified positon. The matrix is
  // used to cache results for each (step, position) key.
  //
  // The following recurence relation is used to solve the problem...
  //
  // count(steps, positon) = count(steps - 1, positon - 1) +
  //                         count(steps - 1, positon + 1)
  // count(0, positon) = 1
  // count(steps, positon) = 0 if steps < 0 or steps >= size
  //
  int64_t count(size_t steps, size_t position, matrix& cache) { // NOLINT
    if (position < 0 || position >= size) {
      // Out of bounds
      return 0;
    } else if (steps == 0) {
      // Base recursive case
      return 1;
    } else if (cache[steps][position] == -1) {
      // Solve this problem if it has not been solved before
      int64_t left = count(steps - 1, position - 1, cache);
      int64_t right = count(steps - 1, position + 1, cache);
      cache[steps][position] = add(left, right, p);
    }
    return cache[steps][position];
  }

  //
  // Calculates the modulo p of the number of unique paths in this dimension for
  // each 0 to steps number of steps.
  //
  void count(size_t steps, size_t position) {
    // Create the memoization cache for all (step, position) keys
    matrix cache(steps + 1, std::vector<int64_t>(size, -1));
    // Initialize the final results cache
    counts = std::vector<int64_t>(steps + 1);
    // Calculate steps(s, position) for all 0 <= s <= steps
    for (size_t s = 0; s <= steps; s++) {
      counts[s] = count(s, position, cache);
    }
  }

 public:
  OneDimensionalPaths(size_t steps, size_t size, size_t position, int64_t p) :
      size(size), p(p) {
    count(steps, position);
  }

  //
  // Returns the count % p for the number of unique paths with this many steps
  // in this dimension.
  //
  int64_t count(size_t steps) {
    return counts[steps];
  }
};

//
// Calculates the modulo p number of unique paths in across multiple dimensions
// given a starting point and number of steps.
//
class MultiDimensionalPaths {
 private:
  typedef std::vector<std::vector<int64_t>> matrix;

  //
  // One dimensional path count calculators for each dimension
  //
  std::vector<OneDimensionalPaths> dimensions;

  //
  // Cached count % p for all 0 to steps for each dimension
  //
  matrix cache;

  //
  // Combinations calculator
  //
  nCr<uint64_t> ncr;

  //
  // Prime number used to compute modulo count
  //
  int64_t p;

  //
  // Calculates the modulo p number of unique paths with the specified number of
  // steps in the first dim dimensions.
  //
  // The following recurence relation is used to solve the problem...
  //
  // count*(steps, dim) = The number of unique paths in a single dimension dim
  //                      with the specified number of steps.
  //
  // count(steps, dim) =
  //     count*(0, dim) * count(steps, dim - 1) * nCr(0, steps) +
  //     count*(1, dim) * count(steps - 1, dim - 1) * nCr(1, steps) +
  //     count*(2, dim) * count(steps - 2, dim - 1) * nCr(2, steps) +
  //     ...
  //     count*(steps, dim) * count(0, dim - 1) * nCr(steps, steps)
  //
  // term(steps, dim, i) =
  //     count*(i, dim) * count(steps - i, dim - 1) * nCr(i, steps)
  //
  // Each term(steps, dim, i) represents the number of unique paths where the
  // first i steps are all in the dimension dim. The remaining steps - i steps
  // are in the next dim - 1 dimensions which is defined recursively.
  //
  // The nCr(i, steps) in each term represents the i positions amongst steps
  // steps which are assigned to the i steps in dimension dim. This calculates
  // the number of step orderings we have amongst dimension dim and dimensions
  // 0 to dim - 1.
  //
  // Heavy use of DP/memoization is used to make this recursion exremely
  // efficient.
  //
  int64_t count(size_t steps, size_t dim) {
    if (dim == 0) {
      return dimensions[dim].count(steps);
    } else if (cache[dim][steps] != -1) {
      return cache[dim][steps];
    }
    int64_t total = 0;
    for (size_t i = 0; i <= steps; i++) {
      int64_t lower = count(i, dim - 1);
      int64_t here = dimensions[dim].count(steps - i);
      int64_t combinations = ncr.calculate(steps, i);
      int64_t increment = multiply(multiply(lower, here, p), combinations, p);
      total = add(total, increment, p);
    }
    return cache[dim][steps] = total;
  }

 public:
  MultiDimensionalPaths(const std::vector<size_t>& sizes,
                        const std::vector<size_t>& positions,
                        size_t steps,
                        int64_t p) :
                        cache(sizes.size(), std::vector<int64_t>(steps + 1, -1)), // NOLINT
                        ncr(steps, p),
                        p(p) {
    for (size_t dim = 0; dim < sizes.size(); dim++) {
      OneDimensionalPaths path(steps, sizes[dim], positions[dim], p);
      dimensions.push_back(std::move(path));
    }
  }

  int64_t count(size_t steps) {
    return count(steps, dimensions.size() - 1);
  }
};

void test() {
  Args args = Args::parse(std::cin);
  MultiDimensionalPaths paths(args.dimensions, args.position, args.M, MOD);
  std::cout << paths.count(args.M) << std::endl;
}

int main() {
  size_t T;
  std::cin >> T;
  while (T--) {
    test();
  }
  return 0;
}
