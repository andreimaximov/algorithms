#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<int> load_stream(std::istream &in, int n) { // NOLINT
  std::vector<int> sequence(n);
  for (auto it = sequence.begin(); it != sequence.end(); it++) {
    in >> *it;
  }
  return sequence;
}

//
// Finds the LCS of sequences a and b using a precalculated DP array where each
// dp[i][j] resembles LCS of a[:i] and b[:j]. The algorithm starts at the last
// characters of a and b, traverses back following largest LCS, and adds
// characters where a[i] == b[j] to path.
//
template<typename T>
std::vector<T> get_path(const std::vector<T> &a, const std::vector<T> &b,
                        const std::vector<std::vector<size_t>> &dp) {
  size_t n = a.size();
  size_t m = b.size();
  size_t i = dp[n][m];
  std::vector<T> path(i);
  while (n > 0 && m > 0) {
    if (a[n - 1] == b[m - 1]) {
      path[--i] = a[n - 1];
      n--;
      m--;
    } else if (dp[n - 1][m]  > dp[n][m - 1]) {
      n--;
    } else {
      m--;
    }
  }
  return path;
}

//
// Returns the LCS of sequences a and b.
//
template<typename T>
std::vector<T> lcs(const std::vector<T> &a, const std::vector<T> &b) {
  size_t n = a.size() + 1;
  size_t m = b.size() + 1;
  std::vector<std::vector<size_t>> dp(n, std::vector<size_t>(m, 0));

  //
  // Run DP using f(a, b):
  //
  // 1. f(a, b) = 1 + f(a[:-1], b[:-1]) if a[-1] == b[-1]
  // 2. f(a, b) = Max(f(a[:-1], b), f(a, b[:-1])) if a[-1] != b[-1]
  //
  for (size_t i = 1; i < n; i++) {
    for (size_t j = 1; j < m; j++) {
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else {
        dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
      }
    }
  }

  return get_path(a, b, dp);
}

int main() {
  // Load sequences.
  size_t n, m;
  std::cin >> n >> m;
  std::vector<int> a = load_stream(std::cin, n);
  std::vector<int> b = load_stream(std::cin, m);

  // Calculate and print LCS.
  std::vector<int> sequence = lcs(a, b);
  std::copy(sequence.begin(), sequence.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  return 0;
}
