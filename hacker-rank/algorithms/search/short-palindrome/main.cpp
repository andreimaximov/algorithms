#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using std::string;
using std::vector;
using std::transform;
using std::cin;
using std::cout;
using std::endl;

#define MOD 1000000007

//
// Converts a lowercase ASCII char a - z to an int 0 - 25.
//
int chartoint(char c) {
  return c - 'a';
}

//
// Computes (a + b) % MOD
//
inline int add(int a, int b) {
  return (a + b) % MOD;
}

//
// Computes (a - b) % MOD ensuring a positive result
//
inline int sub(int a, int b) {
  return add(MOD, (a - b) % MOD);
}

//
// Computes (a * b) % MOD
//
inline int mul(int a, int b) {
  return ((int64_t) a * (int64_t) b) % MOD;
}

//
// Counts the number of 4-long palindromic subsequences in A. Each element in A
// is expected to take on a value [0...k - 1]. The algorithm takes O(nk) time
// and O(k^2) space.
//
// The essence of the algorithm is that to count all palindromes (a, b, c, d)
// we consider each b in A, and try to see if there is a subsequence (c, d) in
// S after i such that (c, d) = (b, a) in O(k) time. Since we consider O(n)
// such b in S, the overall runtime is O(nk).
//
int short_palindromes(const vector<int>& A, int k) {
  // Count of characters in suffix string S[j + 1:].
  vector<int> suffix_char_counts(k, 0);

  // Count of each two character pattern in suffix string S[j + 1:].
  vector<vector<int>> suffix_pattern_counts(k, vector<int>(k, 0));

  for (int i = A.size() - 1; i >= 0; i --) {
    int c = A[i];
    for (int d = 0; d < k; d++) {
      suffix_pattern_counts[c][d] = add(suffix_pattern_counts[c][d],
                                        suffix_char_counts[d]);
    }
    suffix_char_counts[c] = add(suffix_char_counts[c], 1);
  }

  int total = 0;

  // Count of character in prefix string S[:j].
  vector<int> prefix_char_counts(k, 0);

  for (int b : A) {
    // Update suffix by removing b which is now part of the palindrome "ab"
    // prefix.
    suffix_char_counts[b] = sub(suffix_char_counts[b], 1);
    for (int d = 0; d < k; d++) {
      suffix_pattern_counts[b][d] = sub(suffix_pattern_counts[b][d],
                                        suffix_char_counts[d]);
    }

    // For all "ab" prefixes calculate the number of unique pairings with a
    // "ba" suffix.
    for (int a = 0; a < k; a++) {
      total = add(total, mul(prefix_char_counts[a],
                             suffix_pattern_counts[b][a]));
    }

    // Update the prefix character counts
    prefix_char_counts[b] = add(prefix_char_counts[b], 1);
  }

  return total;
}

int main() {
  string S;
  cin >> S;
  vector<int> A(S.size());
  transform(S.begin(), S.end(), A.begin(), chartoint);
  cout << short_palindromes(A, 26) << endl;
  return 0;
}
