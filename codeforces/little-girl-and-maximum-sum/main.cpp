#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr int MAX_N = 200010;

// Original sequence.
int A[MAX_N];

// Sum D[0...i] is the number of times number i appears in a query.
int64_t D[MAX_N];

int main() {
  ios::sync_with_stdio(false);

  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    D[l]++;
    D[r + 1]--;
  }

  // Reduce D. (See comment at top)
  for (int i = 1; i <= n; i++) {
    D[i] = D[i - 1] + D[i];
  }

  // Place the largest numbers in positions that most commonly occur in queries.
  sort(A, A + n);
  sort(D + 1, D + n + 1);

  int64_t sum = 0;

  for (int i = 0; i < n; i++) {
    sum += A[i] * D[i + 1];
  }

  cout << sum << endl;

  return 0;
}

