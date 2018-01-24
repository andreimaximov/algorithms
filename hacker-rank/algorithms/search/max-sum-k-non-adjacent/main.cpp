#include <iostream>
#include <vector>

class Calculator {
 private:
  typedef std::vector<std::vector<int>> matrix;

  matrix cache;

  /**
   * Calculates the largest sum of K non-adjacent numbers in amongst the first
   * N elements of the vector. This is done with the following recurrence
   * relation.
   *
   * A = An array/vector of N numbers with index starting at 1.
   *
   * MaxSum(A, K, N) = Max(MaxSum(A, K, N - 1), A[N] + MaxSum(A, K - 1, N - 2))
   *
   * The first argument to Max, MaxSum(A, K, N - 1), is the largest sum of K
   * non-consecutive integers in the first N - 1 numbers of the array. This
   * does not include A[N].
   *
   * The second argument, A[N] + MaxSum(A, K - 1, N - 2), calculates the largest
   * sum of K non-consecutive numbers in the array if A[N] is one of those
   * numbers.
   *
   * We then just take the maximum of these 2 calculations. The algorithm is
   * improved using dynamic programming to cache MaxSum(A, K, N) calls using a
   * K x N matrix. Thus, the algorithm has O(KN) complexity.
   *
   * @return The largest sum of K non-adjacent numbers of the first N numbers in
   * the vector.
   */
  int maxsum(const std::vector<int>& numbers, int K, int N) {
    uint64_t minN = K + K - 1;
    if (N < minN) {
      return -1;
    }
    if (cache[K - 1][N - 1] != -1) {
      return cache[K - 1][N - 1];
    }
    if (K == 1) {
      if (N == 1) {
        return numbers[0];
      }
      int exclusive = this->maxsum(numbers, 1, N - 1);
      cache[K - 1][N - 1] = std::max(numbers[N - 1], exclusive);
    } else {
      int inclusive = this->maxsum(numbers, K - 1, N - 2);
      if (inclusive != -1) {
        inclusive += numbers[N - 1];
      }
      int exclusive = this->maxsum(numbers, K, N - 1);
      cache[K - 1][N - 1] = std::max(inclusive, exclusive);
    }
    return cache[K - 1][N - 1];
  }

 public:
  /**
   * Calculates the largest sum of K non-adjacent numbers in the vector.
   *
   * @return The largest sum or 0 if there is no way to pick K non-adjacent
   *         numbers.
   */
  int maxsum(const std::vector<int>& numbers, int K) {
    this->cache = matrix(K, std::vector<int>(numbers.size(), -1));
    return this->maxsum(numbers, K, numbers.size());
  }
};

int test() {
  size_t N, K;
  std::cin >> N >> K;
  std::vector<int> nums(N);
  for (auto it = nums.begin(); it != nums.end(); ++it) {
    std::cin >> *it;
  }
  Calculator calculator;
  return calculator.maxsum(nums, K);
}

int main() {
  size_t T;
  std::cin >> T;
  while (T-- > 0) {
    std::cout << test() << std::endl;
  }
  return 0;
}
