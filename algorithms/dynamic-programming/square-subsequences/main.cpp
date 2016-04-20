#include <iostream>
#include <vector>
#include <stdexcept>

const uint32_t MOD = 1000000007;

const size_t MAX_LENGTH = 200;

typedef std::vector<std::vector<uint32_t>> matrix;

/**
 * The class substring presents an efficient substring view of a string by
 * using an offset and source string reference to avoid copy substrings.
 */
class substring {
 private:
  const std::string& source;

  size_t start;

  size_t end;

 public:
  substring(const std::string& source, size_t start, size_t end) :
    source(source), start(start), end(end) {
  }

  const char& operator[](size_t i) const {
    if (i >= this->length()) {
      throw std::invalid_argument("Out of bounds!");
    }
    return this->source[this->start + i];
  }

  size_t length() const {
    return this->end - this->start + 1;
  }
};

uint32_t add(const uint32_t& a, const uint32_t& b) {
  return ((uint64_t) a + b) % MOD;
}

uint32_t sub(const uint32_t& a, const uint32_t& b) {
  return ((uint64_t) a - b + MOD) % MOD;
}

template<class S, class C>
uint32_t common(const S& a, const S& b, C& cache) { // NOLINT
  cache[0][0] = 1;

  for (size_t j = 0; j <= a.length(); j++) {
    for (size_t k = 0; k <= b.length(); k++) {
      if (j > 0 || k > 0) {
        cache[j][k] = 0;
      }
      if (j > 0) {
        cache[j][k] = add(cache[j][k], cache[j - 1][k]);
      }
      if (k > 0) {
        cache[j][k] = add(cache[j][k], cache[j][k - 1]);
      }
      if (j > 0 && k > 0 && a[j - 1] != b[k - 1]) {
        cache[j][k] = sub(cache[j][k], cache[j - 1][k - 1]);
      }
    }
  }

  uint32_t count = 0;
  for (size_t k = 0; k < b.length(); k++) {
    if (a[a.length() - 1] == b[k]) {
      count = add(count, cache[a.length() - 1][k]);
    }
  }
  return count;
}

uint32_t countss(const std::string& str, matrix& cache) { // NOLINT
  uint32_t count = 0;
  for (size_t i = 0; i < str.length() - 1; i++) {
    substring a(str, 0, i);
    substring b(str, i + 1, str.length() - 1);
    count = add(count, common<substring, matrix>(a, b, cache));
  }
  return count;
}

uint32_t countss(const std::string& str) {
  matrix cache(MAX_LENGTH + 1, std::vector<uint32_t>(MAX_LENGTH + 1, 0));
  return countss(str, cache);
}

int main() {
  uint16_t T;
  std::string S;
  std::cin >> T;
  while (T--) {
    std::cin >> S;
    std::cout << countss(S) << std::endl;
  }
  return 0;
}
