#include <bits/stdc++.h>

using namespace std;  // NOLINT

/**
 * The most operations we will have to do is N - 1 which is stacking all the
 * building together into one.
 */
constexpr int MAX_N = 5000;

constexpr int INF = numeric_limits<int>::max();

constexpr bool TUTORIAL = true;

/**
 * The number of buildings.
 */
int N;

/**
 * Stores height of each building.
 */
int H[MAX_N + 1];

/**
 * This array means 2 different things for (1) my original solution and (2)
 * the tutorial based solution.
 *
 * (1) Each DP[n][i] stores (i) the height of the last building after
 * beautifying H[0...i] in <= n operations or (ii) -1 if it is not possible to
 * do so.
 *
 * (2) Each DP[i][n] stores the height of the lowest last towers after
 * beautifying  buildings 0...i into at least n towers.
 */
int DP[MAX_N + 1][MAX_N + 1];

/**
 * Original O(n^3) implementation - more complex than tutorial solution but
 * passes in time limit.
 */
int solution() {
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

    // Check if we can beautify all N buildsings in n ops.
    if (DP[n][N - 1] != -1) {
      return n;
    }
  }

  return N - 1;
}

/**
 * Tutorial based O(n^2) implementation - also simpler than my original
 * solution.
 */
int tutorial() {
  // Handle our base case - DP for just the first building.
  DP[0][0] = DP[0][1] = H[0];
  for (int n = 2; n <= N; n++) {
    DP[0][n] = -1;
  }

  for (int j = 1; j < N; j++) {
    // For case n = 1 we can try to just stack this building on top of the
    // stack of all previous buildings.
    DP[j][0] = DP[j][1] = DP[j - 1][1] + H[j];

    // S = the smallest sum H[i] + ... + H[j] such that S >= DP[i - 1][n - 1]
    // at each iteration. This is essentially the height of the smallest
    // stack of buildings we can have as the last tower for each n. We need to
    // be very careful that we compute this suffix sum at first and NOT
    // H[0] + ... H[j]. It appears like the next stage can be modified to
    // essentially trim H[0] + ... + H[j] from the left but this is messy
    // since DP[k][n - 1] > H[k + 1] + ... H[j] does NOT rule out the existence
    // of m > k such that DP[m][n - 1] <= H[m + 1] + ... + H[j]. We can avoid
    // this messy case by just calculating this initial S from the right.
    int i = j;
    int S = H[j];
    while (i > 0 && S < DP[i - 1][1]) {
      i--;
      S += H[i];
    }

    if (i == 0) {
      // If we cannot beautify H[0] ... H[j] into at least 2 towers then we
      // cannot beautify by stacking into 3, 4 ... N - 1 towers either.
      for (int n = 2; n <= N; n++) {
        DP[j][n] = -1;
      }
    } else {
      // Use the fact that DP[i][n] <= DP[i][n - 1] if DP[i][n] != -1.
      for (int n = 2; n <= N; n++) {
        // Pull up i until we can beautify the previous H[0] ... H[i - 1] into
        // at least n - 1 towers.
        while (i < j && DP[i - 1][n - 1] == -1) {
          S -= H[i];
          i++;
        }

        if (DP[i - 1][n - 1] == -1 || S < DP[i - 1][n - 1]) {
          DP[j][n] = -1;
        } else {
          // Decrease the tail S as much as possible while keeping it at least
          // as tall as the last tower in the previous segment.
          while (i < j && S - H[i] >= DP[i][n - 1]) {
            S -= H[i];
            i++;
          }

          // Sanity check...
          assert(DP[i - 1][n - 1] != -1 && DP[i - 1][n - 1] <= S);

          DP[j][n] = S;
        }
      }
    }

    // Finally calculcate DP[i][n] = min(DP[i][n + 1], DP[i][n + 2] ...)
    for (int n = N - 1; n >= 0; n--) {
      if (DP[j][n + 1] != -1) {
        DP[j][n] = min(DP[j][n], DP[j][n + 1]);
      }
    }
  }

  // Search for the largest number of towers we can have, and thus the least
  // number of ops, to get a beautified city.
  for (int n = N; n > 0; n--) {
    if (DP[N - 1][n] != -1) {
      return N - n;
    }
  }

  return N - 1;
}

int main() {
  cin >> N;

  if (N < 2) {
    cout << 0 << endl;
    return 0;
  }

  for (int i = 0; i < N; i++) {
    cin >> H[i];
  }

  if (TUTORIAL) {
    cout << tutorial() << endl;
  } else {
    cout << solution() << endl;
  }

  return 0;
}

