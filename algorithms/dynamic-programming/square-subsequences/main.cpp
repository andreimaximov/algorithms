#include <iostream>
#include <array>

const uint32_t MOD = 1000000007;

const size_t MAX_LENGTH = 200;

//
// Safely calculates (a + b) % MOD
//
int add(int a, int b) {
  return ((int64_t) a + b) % MOD;
}

//
// Safely calculates (a - b) % MOD
//
int sub(int a, int b) {
  return ((int64_t) a - b + MOD) % MOD;
}

//
// Calculates the number of subsequences in common between L = s[0...p] and
// R = s[p + 1...n] where each subsequence ends with s[p]. Takes
// O(length(L) * length(R)) time.
//
int common(const std::string& s, int p) {
  // Each dp[i][j] is the number of common subsequences in the first i
  // characters of L and the first j characters of R.
  int dp[MAX_LENGTH][MAX_LENGTH] = {{0}};

  // Length of L = s[0...p].
  int n = p + 1;

  // Length of R = s[p + 1...n].
  int m = s.size() - n;

  // Base case - Length of longest common subsequences between "" and x where
  // |x| > 0 is 1. (The empty subsequence)
  for (int i = 0; i <= n; i++) {
    dp[i][0] = 1;
  }

  for (int j = 0; j <= m; j++) {
    dp[0][j] = 1;
  }

  //
  // Consider function f(i, j) = The number of common subsequences between
  // L[0...i - 1] and R[0...j - 1]. We have already described the base case
  // H(*, 0) = H(0, *) = 1 above. The two recursive cases are as follows.
  //
  // 1. H(i, j) = H(i, j - 1) + H(i - 1, j) - H(i - 1, j - 1) if
  //    L[i - 1] != R[j - 1]. We must subtract H(i - 1, j - 1) to avoid double
  //    counting subsequences. (Inclusion Exclusion Principle)
  //
  // 2. H(i, j) = H(i, j - 1) + H(i - 1, j) - H(i - 1, j - 1) + H(i - 1, j - 1)
  //    = H(i - 1, j) + H(i, j - 1) if L[i - 1] == R[j - 1]. We must consider
  //    common subsequences counted by H(i - 1, j - 1) as a prefix to the
  //    common subsequences ending with L[i - 1] == R[j - 1].
  //
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = add(dp[i][j], dp[i - 1][j]);

      dp[i][j] = add(dp[i][j], dp[i][j - 1]);

      if (s[i - 1] != s[p + j]) {
        dp[i][j] = sub(dp[i][j], dp[i - 1][j - 1]);
      }
    }
  }

  //
  // Count only the common subsequences ending with s[p] - the last character
  // of L.
  //
  int count = 0;

  for (int j = 0; j < m; j++) {
    if (s[p] == s[p + j + 1]) {
      count = add(count, dp[p][j]);
    }
  }

  return count;
}

//
// Counts the square subsequences in s. The idea behind the algorithm is to...
//
// 1. Consider all partitions s = LR of s where |L| > 0 and |R| > 0
//
// 2. Count the number of subsequences shared between each L and R ending with
//    the last character of L. This is important because it forms a partition
//    boundary so that we do not double count any subsequences across different
//    partitions.
//
int countss(const std::string& s) {
  int count = 0;
  for (size_t p = 0; p < s.length() - 1; p++) {
    count = add(count, common(s, p));
  }
  return count;
}

int main() {
  int T;
  std::string S;
  std::cin >> T;
  while (T--) {
    std::cin >> S;
    std::cout << countss(S) << std::endl;
  }
  return 0;
}
