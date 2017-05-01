#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr int MAX_N = 200000;

int N, M, S, D;

int X[MAX_N + 10];

/**
 * Each DP[i] indicates if it is possible to reach position M after jumping to
 * the spot immediately after obstacle i. 0 => Unknown, 1 => Possible,
 * 2 => NOT possible.
 */
int DP[MAX_N + 1] = { 0 };

stack<string> OPS;

void run(int x) {
  if (x == 0) return;

  std::ostringstream os;
  os << "RUN " << x;
  OPS.push(os.str());
}

void jump(int x) {
  assert(x > 0);

  std::ostringstream os;
  os << "JUMP " << x;
  OPS.push(os.str());
}

bool dfs(int p) {
  assert(p >= 0 && p <= N);

  if (DP[p] != 0) {
    // We should not be calling again for a p that previous returned true since
    // true should propagate all the way back up.
    assert(DP[p] == 2);
    return false;
  }

  if (M < X[p]) {
    // Whoa, overshoot!
    DP[p] = 2;
    return false;
  }

  if (p == N || M < X[p + 1]) {
    // Cool, target is between last and next obstacle so run directly to it.
    run(M - X[p] - 1);
    DP[p] = 1;
  } else {
    DP[p] = 2;

    // Check if there is space for a minimal runup of at least length S.
    int space = X[p + 1] - X[p] - 2;
    if (space < S) {
      return false;
    }

    int i = p + 1;

    // Search by jumping over all possible obstacles from current runup.
    while (DP[p] != 1 && i <= N && X[i] + 1 <= X[p + 1] - 1 + D) {
      if (dfs(i)) {
        DP[p] = 1;
        jump(X[i] + 1 - X[p + 1] + 1);
        run(space);
      }
      i++;
    }
  }

  return DP[p] == 1;
}

int main() {
  cin >> N >> M >> S >> D;

  X[0] = -1;
  for (int i = 0; i < N; i++) {
    cin >> X[i + 1];
  }
  sort(&X[0], &X[N + 1]);

  if (!dfs(0)) {
    printf("IMPOSSIBLE\n");
  } else {
    while (!OPS.empty()) {
      cout << OPS.top() << endl;
      OPS.pop();
    }
  }

  return 0;
}

