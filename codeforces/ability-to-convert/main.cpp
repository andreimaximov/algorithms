#include <bits/stdc++.h>

using namespace std;  // NOLINT

//
// Entry for optimal decoding of a suffix of a string k.
//
struct cache {
  //
  // The minimal decoding.
  //
  uint64_t n;

  //
  // If the encoding in the original base has i digits, this is base^i. This is
  // essentially the value we need to multiply a digit x if we wish to prepend
  // x to the original encoding.
  //
  uint64_t power;
};

string convert(uint32_t n, const string& k) {
  // Track optimal encoding for each suffix k[i...].
  vector<cache> dp(k.size() + 1);
  dp[k.size()] = {0, 1};

  for (int i = k.size() - 1; i >= 0; i--) {
    // 0 is the only digit that can start with a 0 in an encoding. Multiple 0's
    // are not valid.
    if (k[i] == '0') {
      dp[i] = {dp[i + 1].n, dp[i + 1].power * n};
      continue;
    }

    //
    // For each suffix k[i...] consider possible splits k[i...j]k[j + 1...].
    //
    for (size_t j = i; j < k.size(); j++) {
      uint64_t prefix = stoull(k.substr(i, j - i + 1));
      if (prefix >= n) {
        break;
      }

      uint64_t power = dp[j + 1].power;

      // The result is <= 10^18, so make sure we do not encounter overflow
      // when using uint64_t which has an upper bound > 10^18 to consider a
      // candidate decoding.
      if (numeric_limits<uint64_t>::max() / prefix < power) {
        continue;
      }

      // Compute a candidate an duse it if it is better than en existing one
      // for suffix k[i...].
      uint64_t x = prefix * power + dp[j + 1].n;
      if (dp[i].power == 0 || x < dp[i].n) {
        dp[i] = {x, power * n};
      }
    }
  }

  return to_string(dp[0].n);
}

int main() {
  uint32_t n;
  cin >> n;
  string k;
  cin >> k;

  cout << convert(n, k) << endl;
  return 0;
}

