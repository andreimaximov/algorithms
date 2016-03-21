#include <iostream>
#include <vector>

const uint64_t MOD = 1000000000;

class nCr {
 private:
  std::vector<std::vector<uint64_t>> cache;

  uint64_t mod;

 public:
  nCr(uint64_t n, uint64_t mod) :
    cache(n, std::vector<uint64_t>(n, 0)),
    mod(mod) {
  }

  uint64_t calculate(uint64_t n, uint64_t r) {
    if (n == 0 || r == 0 || r == n) {
      return 1;
    } else if (this->cache[n - 1][r - 1] != 0) {
      return this->cache[n - 1][r - 1];
    }
    uint64_t a = this->calculate(n - 1, r - 1);
    uint64_t b = this->calculate(n - 1, r);
    this->cache[n - 1][r - 1] = (a % this->mod + b % this->mod) % this->mod;
    return this->cache[n - 1][r - 1];
  }
};

void run(uint16_t n, std::ostream &out) { // NOLINT
  nCr ncr(n, MOD);
  for (uint16_t r = 0; r <= n; r++) {
    out << ncr.calculate(n, r) << " ";
  }
  out << std::endl;
}

int main() {
  uint16_t T;
  std::cin >> T;
  while (T--) {
    uint16_t n;
    std::cin >> n;
    run(n, std::cout);
  }
}
