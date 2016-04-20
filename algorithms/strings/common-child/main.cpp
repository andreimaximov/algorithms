#include <iostream>
#include <vector>
#include <string>

uint32_t lcs(const std::string& a, const std::string& b) {
  size_t m = a.length() + 1;
  size_t n = b.length() + 1;
  std::vector<std::vector<uint32_t>> cache(m, std::vector<uint32_t>(n));
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i == 0 || j == 0) {
        cache[i][j] = 0;
      } else if (a[i - 1] == b[j - 1]) {
        cache[i][j] = cache[i - 1][j - 1] + 1;
      } else {
        cache[i][j] = std::max(cache[i][j - 1],  cache[i - 1][j]);
      }
    }
  }
  return cache[a.length()][b.length()];
}

int main() {
  std::string a, b;
  std::cin >> a;
  std::cin >> b;
  std::cout << lcs(a, b) << std::endl;
  return 0;
}
