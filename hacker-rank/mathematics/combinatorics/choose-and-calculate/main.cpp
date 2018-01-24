#include <iostream>
#include <vector>
#include <algorithm>

const uint32_t MOD = 1000000007;

/**
 * Calculates a^b % p in logarithmic time
 */
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

/**
 * Calculates modular inverse of a mod prime p using Fermat's Little Theorem.
 */
uint64_t modinv(uint64_t a, uint64_t p) {
  return modpow(a, p - 2, p);
}

/**
 * Calculates nCr % p using the following technique.
 *
 * C(n, r) = n!/((n-r)!r!)
 *
 * C(n, r) % p = n! % p * (n-r)!^-1 % p * r!^-1 % p
 *
 * f(n) = n! % p
 * g(n) = n!^-1 % p = (f(n) % p)^-1 % p
 *
 * C(n, r) % p = (f(n) * g(n-r) * g(r)) % p
 */
template<typename T>
class nCr {
 private:
  std::vector<T> f;

  std::vector<T> g;

  T p;

  void pre() {
    this->f[0] = 1;
    for (size_t i = 1; i < this->f.size(); i++) {
      this->f[i] = (this->f[i - 1] * i % this->p) % this->p;
    }
    this->g[0] = 0;
    for (size_t i = 1; i < this->g.size(); i++) {
      this->g[i] = modinv(this->f[i], this->p);
    }
  }

 public:
  nCr(size_t n, T p) :
    f(n + 1),
    g(n + 1),
    p(p) {
    this->pre();
  }

  T calculate(size_t n, size_t r) {
    if (r > n) {
      return 0;
    } else if (n == 0 || r == 0 || r == n) {
      return 1;
    }
    return this->f[n] * this->g[n - r] % this->p * this->g[r] % this->p;
  }
};

/**
 * For each Xi in sorted nums of size n, we need to calculate a = # of ways
 * such that Xi is max of K numbers and b = # of ways such that Xi is the
 * minimum of K numbers.
 *
 * a = C(i, K - 1) because we need to choose K - 1 numbers <= Xi
 * b = C(n - i - 1, K - 1) because we need to choose K - 1 numbers >= Xi
 *
 * We calculate and sum all Xi * (a - b) % p for all Xi in nums to get the
 * total.
 */
template<typename T>
uint64_t run(const std::vector<T> &nums, size_t K) {
  nCr<uint64_t> ncr(nums.size(), MOD);

  int64_t sum = 0;

  for (int i = K - 1; i < nums.size(); i++) {
    sum += nums[i] * ncr.calculate(i, K - 1) % MOD;
  }

  for (int i = 0; i < nums.size() - K + 1; i++) {
    sum -= nums[i] * ncr.calculate(nums.size() - i - 1, K - 1) % MOD;
  }

  return (sum % MOD + MOD) % MOD;
}

int main() {
  size_t N, K;
  std::cin >> N >> K;

  std::vector<uint32_t> nums(N);
  for (int i = 0; i < N; i++) {
    std::cin >> nums[i];
  }
  std::sort(nums.begin(), nums.end());

  std::cout << run<uint32_t>(nums, K) << std::endl;
}
