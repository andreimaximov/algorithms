#include <iostream>
#include <vector>

std::vector<int> build(int length) {
  std::vector<int> sequence(length);
  for (size_t i = 0; i < length; ++i) {
    std::cin >> sequence[i];
  }
  return sequence;
}

//  Returns index of ceil of value in tails. (i.e. the smallest element greater
//  than value)
int searchceil(const std::vector<int>& tails, size_t last, int value) {
  size_t left = 0, right = last;
  while (right > left + 1) {
    size_t mid = (left + right)/2;  // Works because tails.size() <= 10^6.
    if (tails[mid] >= value) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}

int lis(const std::vector<int>& sequence) {
  std::vector<int> tails(sequence.size());
  tails[0] = sequence[0];
  size_t last = 0;
  for (size_t i = 1; i < sequence.size(); i++) {
    if (sequence[i] <= tails[0]) {
      tails[0] = sequence[i];
    } else if (sequence[i] > tails[last]) {
      tails[++last] = sequence[i];
    } else {
      size_t existing_index = searchceil(tails, last, sequence[i]);
      tails[existing_index] = sequence[i];
    }
  }
  return last + 1;
}

int main() {
  int N;
  std::cin >> N;
  std::vector<int> sequence = build(N);
  std::cout << lis(sequence);
  return 0;
}
