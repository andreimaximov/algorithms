#include <iostream>
#include <vector>

#define RANGE 101

typedef std::vector<int> list;

template<typename T>
struct inc {
  inline T operator()(const T& value) {
    return value + 1;
  }
};

template<typename T>
struct dec {
  inline T operator()(const T& value) {
    return value - 1;
  }
};

template<typename Operator>
int calculate(list& frequencies, list& numbers, int begin) { // NOLINT
  Operator op;
  int size;
  std::cin >> size;
  while (size-- > 0) {
    int n;
    std::cin >> n;
    int index = n % RANGE;  // Index where we want to place this number
    frequencies[index] = op(frequencies[index]);
    numbers[index] = n;
    if (begin == -1 || n < numbers[begin]) {
      begin = index;
    }
  }
  return begin;
}

int main() {
  std::vector<int> frequencies(RANGE, 0);
  std::vector<int> numbers(RANGE, 0);

  int begin = -1;
  begin = calculate<inc<int>>(frequencies, numbers, begin);
  begin = calculate<dec<int>>(frequencies, numbers, begin);

  for (size_t i = 0; i < frequencies.size(); ++i) {
    size_t index = (i + begin) % (RANGE - 1);
    if (frequencies[index] != 0) {
      std::cout << numbers[index] << " ";
    }
  }
  std::cout << std::endl;
}
