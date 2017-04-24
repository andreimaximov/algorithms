#include <bits/stdc++.h>

using namespace std;  // NOLINT

/**
 * The most operations we will have to do is N - 1 which is stacking all the
 * building together into one.
 */
constexpr int MAX_N = 5000;

constexpr int INF = numeric_limits<int>::max();

/**
 * The number of buildings.
 */
int N;

/**
 * Stores height of each building.
 */
int H[MAX_N + 1];

/**
 * Each dp[n][i] stores (i) the height of the last building after beautifying
 * H[0...i] in <= n operations or (ii) -1 if it is not not possible to do so.
 */
int DP[MAX_N + 1][MAX_N + 1];

int main() {
  cin >> N;

  if (N < 2) {
    cout << 0 << endl;
    return 0;
  }

  for (int i = 0; i < N; i++) {
    cin >> H[i];
  }

  // Fill in DP[0][i] for all i. We are effectively checking if the city is
  // already beautiful.
  DP[0][0] = H[0];

  for (int i = 1; i < N; i++) {
    if (DP[0][i - 1] == -1) {
      DP[0][i] = -1;  // Beauty issue earlier in the city!
    } else {
      DP[0][i] = (H[i] >= H[i - 1]) ? H[i] : -1;  // Non-decreasing height?
    }
  }

  // Check if city is already beautiful.
  if (DP[0][N - 1] != -1) {
    cout << 0 << endl;
    return 0;
  }

  // Search for the smallest number of operations that can beautify thie city.
  for (int n = 1; n < N; n++) {
    DP[n][0] = H[0];

    // Calculate DP[n][i] for all H[0...i] to building up DP[n][N - 1].
    for (int i = 1; i < N; i++) {
      DP[n][i] = INF;

      // Check if we can beautify H[0...i] in < n ops.
      if (DP[n - 1][i] != -1) {
        DP[n][i] = min(DP[n][i], DP[n - 1][i]);
      }

      // Check if we can beautify H[0...i] in <= n ops by keeping H[i] separate
      // at the very end.
      if (DP[n][i - 1] != -1 && DP[n][i - 1] <= H[i]) {
        DP[n][i] = min(DP[n][i], H[i]);
      }

      // Check if we can beautify H[0...i] in <= n ops by stacking H[i] on top
      // of the building to it's left.
      if (DP[n - 1][i - 1] != -1) {
        DP[n][i] = min(DP[n][i], H[i] + DP[n - 1][i - 1]);
      }

      // We are currently on building i. We are trying to find a slice of the
      // city H[j...i] such that S = sum(H[j...i]), S >= DP[m][j - 1], and S
      // is MINIMAL - important! m is the number of moves left after stacking
      // H[j...i] which takes i - j operations.
      int S = H[i];
      for (int m = n - 1; m >= 0; m--) {
        int j = i - (n - m);
        S += H[j];

        //
        // Check for (i) if there is no in bounds j with a slice H[j...i] of
        // length n - m + 1 or (ii) if DP[m][j - 1] is invalid - no prefix
        // exists for the slice.
        //
        // Why can we terminate our search here? Say DP[m][j] != -1 so there
        // exists a valid set of <= m operations to beautify H[0...j]. Thus,
        // DP[m + 1][j + 1] <= DP[m][j] because we can always just stack
        // H[j + 1] on top of the last building in the beautification of
        // H[0...j] in m operations.
        //
        // Thus DP[m][j - 1] == -1 -> D[m - 1][j] = -1 (next iteration) for
        // the rest of the loop.
        //
        if (j < 0 || (j > 0 && DP[m][j - 1] == -1)) break;

        // Check if stacking together H[j...i] does not create a decreasing
        // height when appended to optimal (lowest height) beautification of
        // H[0...j - 1].
        if ((j == 0) || S >= DP[m][j - 1]) {
          DP[n][i] = min(DP[n][i], S);
          break;
        }
      }

      // Mark DP[n][i] as impossible if still at infinity.
      DP[n][i] = (DP[n][i] == INF) ? -1 : DP[n][i];
    }

    if (DP[n][N - 1] != -1) {
      cout << n << endl;
      return 0;
    }
  }

  return 0;
}

