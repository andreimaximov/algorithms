#include <iostream>
#include <vector>
#include <iterator>

typedef std::vector<std::vector<int>> matrix;

std::vector<int> build(int length) {
  std::vector<int> sequence(length);
  for (size_t i = 0; i < length; ++i) {
    std::cin >> sequence[i];
  }
  return sequence;
}

matrix _lcs(const std::vector<int>& a, const std::vector<int>& b) {
  int n = a.size() + 1;
  int m = b.size() + 1;
  matrix cache(n, std::vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == 0 || j == 0) {
        cache[i][j] = 0;
      } else if (a[i - 1] == b[j - 1]) {
        cache[i][j] = cache[i - 1][j - 1] + 1;
      } else {
        cache[i][j] = std::max(cache[i][j - 1],  cache[i - 1][j]);
      }
    }
  }
  return cache;
}

std::vector<int> lcs(const std::vector<int>& a, const std::vector<int>& b) {
  matrix cache = _lcs(a, b);
  int n = a.size();
  int m = b.size();
  int index = cache[n][m];

  std::vector<int> subseq(index);

  while (n > 0 && m > 0) {
    if (a[n - 1] == b[m - 1]) {
      subseq[--index] = a[n - 1];
      --n; --m;
    } else if (cache[n - 1][m] > cache[n][m - 1]) {
      --n;
    } else {
      --m;
    }
  }

  return subseq;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a = build(n);
  std::vector<int> b = build(m);

  std::vector<int> subseq = lcs(a, b);
  std::ostream_iterator<int> out(std::cout, " ");
  std::copy(subseq.begin(), subseq.end(), out);
  return 0;
}
