#include <iostream>
#include <vector>
#include <limits>

std::vector<int> build(int N) {
  std::vector<int> array(N);
  for (size_t i = 0; i < array.size(); ++i) {
    std::cin >> array[i];
  }
  return array;
}

template<typename T>
T kadane(const std::vector<T>& array) {
  T all = array[0], here = array[0];
  for (size_t i = 1; i < array.size(); ++i) {
    here = std::max(array[i], here + array[i]);
    all = std::max(all, here);
  }
  return all;
}

template<typename T>
T max_noncontig_sum(const std::vector<T>& array) {
  T max = std::numeric_limits<T>::min();
  T current = 0;
  for (size_t i = 0; i < array.size(); ++i) {
    current = array[i];
    if (max < 0 && current < 0) {
      max = std::max(max, current);
      continue;
    }
    max = std::max(0, max);
    max += std::max(0, current);
  }
  return max;
}

void test() {
  size_t N = 0;
  std::cin >> N;
  std::cin.ignore();
  std::vector<int> array = build(N);
  int cont = kadane<int>(array);
  int non_cont = max_noncontig_sum<int>(array);
  std::cout << cont << " " << non_cont << std::endl;
}

int main() {
  int T = 0;
  std::cin >> T;
  while (T--) {
      test();
  }
  return 0;
}
