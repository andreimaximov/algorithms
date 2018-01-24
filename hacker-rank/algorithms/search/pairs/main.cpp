#include <iostream>
#include <vector>
#include <queue>

std::priority_queue<int> buildqueue(std::istream& in, int N) { // NOLINT
  std::priority_queue<int> queue;
  int i;
  while (N-- > 0) {
    in >> i;
    queue.push(i);
  }
  return queue;
}

int pairs(std::istream& in, int N, int K) { // NOLINT
  std::priority_queue<int> queue = buildqueue(in, N);

  int index = 0, high = 0, count = 0;
  std::vector<int> numbers(N);
  while (!queue.empty()) {
    numbers[index] = queue.top();
    queue.pop();
    while (high < index && numbers[high] > numbers[index] + K) {
      ++high;
    }
    if (numbers[high] == numbers[index] + K) {
      ++count;
    }
    ++index;
  }

  return count;
}

int main() {
  int N, K;
  std::cin >> N >> K;
  std::cout << pairs(std::cin, N, K) << std::endl;
}
