#include <iostream>
#include <cmath>

typedef uint32_t ultype;

ultype product(ultype A, ultype B) {
  ultype floor_p2 = log2(A), ceil_p2 = log2(B);
  if (ceil_p2 >= floor_p2 + 1) {
    return 0;
  }
  ultype product = A;
  while (A < B) {
    A++;
    product = product & A;
  }
  return product;
}

int main() {
  ultype A, B, T;
  std::cin >> T;
  while (T--) {
    std::cin >> A >> B;
    std::cout << product(A, B) << std::endl;
  }
  return 0;
}
