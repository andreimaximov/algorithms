#include <iostream>

int main() {
  uint32_t T, i;
  std::cin >> T;
  while (T-- > 0) {
    std::cin >> i;
    std::cout << ~i << std::endl;
  }
  return 0;
}
