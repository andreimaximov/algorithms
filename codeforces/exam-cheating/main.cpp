#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr int MAX_N = 1000;

constexpr int MAX_P = 1000;

constexpr int MAX_K = 50;

//
// Loads a bit mask of length n that the genius has answered.
//
vector<bool> load_genius(int n) {
  vector<bool> A(n);
  int r, a;
  cin >> r;
  for (int i = 0; i < r; i++) {
    cin >> a;
    A[a - 1] = true;
  }
  return A;
}

//
// Based on CodeForces #408 tutorial: http://codeforces.com/blog/entry/51527
//
// The main idea is that DP[i][j][a][b] represents the maximum number of
// answers Zane can get correct with exactly j peaks over the first i questions
// with a "overflowing" questions from one genius and b "overflowing" questions
// from the other genius.
//
// An "overflowing" question is one we can see using a previous peek over k
// questions that extends beyond the first i questions.
//
int main() {
  int n, p, k;
  cin >> n >> p >> k;

  vector<bool> X = load_genius(n);
  vector<bool> Y = load_genius(n);

  // The DP algorithm takes O(npk^2) time. However, if p >= 2 * ceil(n / k)
  // then we can glance at all of each geniuses answers so we will get as many
  // answers correct as the geniuses combined. Otherwise if p < 2 * ceil(n / k)
  // the runtime becomes O(n (n / k) k ^2) = O(nkp) which is a viable runtime.
  p = min(p, 2 * ((n + k - 1) / k));

  // We only ever look back 1 i so swap between the current and previous i
  int DP[2][MAX_P + 1][MAX_K][MAX_K];

  // Fill with negatives because we cannot peak before the 1st question so
  // there can be no overflow.
  fill(DP[0][0][0],
       DP[0][0][0] + (sizeof(DP) / sizeof(int)),
       numeric_limits<int>::min());
  DP[0][0][0][0] = 0;

  for (int i = 1; i <= n; i++) {
    int curr = i % 2;
    int prev = (curr + 1) % 2;

    // Consider case where we are making use of "overflow" questions from
    // peak in previous segment.
    for (int j = 1; j <= p; j++) {
      for (int c = 0; c < k - 1; c++) {
        // Use overflow peak from genius X.
        DP[curr][j][c][0] = max(DP[curr][j][c][0],
                                DP[prev][j][c + 1][0] + X[i - 1]);
        // Use overflow peak from genius Y.
        DP[curr][j][0][c] = max(DP[curr][j][0][c],
                                DP[prev][j][0][c + 1] + Y[i - 1]);
      }
    }

    // Consider case where we are peaking starting at i creating more overflow
    // questions.
    for (int j = 1; j <= p; j++) {
      // Peak at i from genius X.
      DP[curr][j][k - 1][0] = max(DP[curr][j][k - 1][0],
                                  DP[prev][j - 1][0][0] + X[i - 1]);
      // Peak at i from genius Y.
      DP[curr][j][0][k - 1] = max(DP[curr][j][0][k - 1],
                                  DP[prev][j - 1][0][0] + Y[i - 1]);
    }

    // Case where we are just using overflow answers from both genius X
    // and Y. Start at j = 2 because we must have at least 2 peaks (one for X
    // and for for Y) available to use.
    for (int j = 2; j <= p; j++) {
      for (int a = 0; a < k - 1; a++) {
        for (int b = 0; b < k - 1; b++) {
          DP[curr][j][a][b] =
            max(DP[curr][j][a][b],
                DP[prev][j][a + 1][b + 1] + (X[i - 1] | Y[i - 1]));
        }
      }
    }

    // Consider case where we are just using overflow from genius one genius
    // and peaking at answer i from the other genius.
    for (int j = 1; j <= p; j++) {
      for (int c = 0; c < k - 1; c++) {
        // Peak at i from genius X.
        DP[curr][j][k - 1][c] =
          max(DP[curr][j][k - 1][c],
              DP[prev][j - 1][0][c + 1] + (X[i - 1] | Y[i - 1]));
        // Peak at i from genius Y.
        DP[curr][j][c][k - 1] =
          max(DP[curr][j][c][k - 1],
              DP[prev][j - 1][c + 1][0] + (X[i - 1] | Y[i - 1]));
      }
    }

    // Simple no peaks with no overflow case
    for (int j = 0; j <= p; j++) {
      DP[curr][j][0][0] = max(DP[curr][j][0][0], DP[prev][j][0][0]);
    }

    // Clean up by setting prev, next curr, to negative values because
    // DP[i][j][a][b] is not "valid" for the case when i + a < k or i + b < k
    // when j >= 1.
    for (int j = 0; j <= p; j++) {
      for (int a = 0; a < k; a++) {
        for (int b = 0; b < k; b++) {
          DP[prev][j][a][b] = numeric_limits<int>::min();
        }
      }
    }
  }

  // Aggregate max correct answers from first n questions using up to p peaks
  // with any number of trailing "overflow" answers.
  int correct = 0;
  for (int j = 1; j <= p; j++) {
    for (int a = 0; a < k; a++) {
      for (int b = 0; b < k; b++) {
        correct = max(correct, DP[n % 2][j][a][b]);
      }
    }
  }
  cout << correct << endl;

  return 0;
}

