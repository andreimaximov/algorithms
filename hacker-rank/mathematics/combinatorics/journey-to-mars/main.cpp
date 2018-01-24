#include <iostream>
#include <cmath>

/**
 * Returns an integer equal to the first K digits of 2^N.
 */
uint64_t first_k(int N, int K) {
  long double f = N * std::log10(2.0L);
  f -= static_cast<uint64_t>(f);
  f = std::pow(10.0, f);
  f *= std::pow(10, K - 1);
  return f;
}

/**
 * Returns an integer equal to the last K digits of 2^log10(mod)
 */
uint64_t last_k(const int& N, const int& mod) {
  if (N == 0) {
    return 1;
  } else if (N % 2 == 0) {
    uint64_t mod_root = last_k(N / 2, mod) % mod;
    return (mod_root * mod_root) % mod;
  } else {
    return (2 * last_k(N - 1, mod)) % mod;
  }
}

int main() {
  int T, N, K;
  std::cin >> T;
  while (T-- > 0) {
    std::cin >> N >> K;
    uint64_t first = first_k(N - 1, K);
    uint64_t last = last_k(N - 1, static_cast<uint64_t>(std::pow(10, K)));
    std::cout << first + last << std::endl;
  }
  return 0;
}
