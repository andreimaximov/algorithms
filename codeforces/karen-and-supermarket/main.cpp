#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr int MAX_N = 5000;

constexpr int MAX_B = 1000000000;

constexpr int INF = MAX_B + 1;

int n, b;

int64_t C[MAX_N], D[MAX_N], X[MAX_N];

/**
 * T[u] = The set of coupons that can be used after using coupon u.
 */
vector<int> T[MAX_N];

/**
 * S[u] = The size of the sub-tree rooted at u.
 */
int S[MAX_N];

/**
 * F[u][i] = The minimum cost to buy exactly i items from the sub-tree rooted
 * at u using coupons.
 */
int64_t F[MAX_N][MAX_N + 1];

/**
 * G[u][i] = The minimum cost to buy exactly i items from the sub-tree rooted
 * at u WITHOUT using coupons.
 */
int64_t G[MAX_N][MAX_N + 1];

/**
 * Calculates F[v][*] and G[v][*] for all v in the sub-tree rooted at u.
 */
void dfs(int u) {
  assert(u >= 0 && u < n);

  // This is important to enforce coupon dependencies! Especially in line 58
  // when i = 0 but we must buy/use coupon u to use coupons further down the
  // tree.
  F[u][0] = INF;
  F[u][1] = C[u] - D[u];

  G[u][0] = 0;
  G[u][1] = C[u];

  S[u] = 1;

  for (int v : T[u]) {
    dfs(v);

    for (int i = S[u]; i >= 0; i--) {
      for (int k = S[v]; k >= 0; k--) {
        // We can use a coupon if we bought the parent with a coupon. If we
        // also buy item u with a coupon then we can also make use of coupons
        // with purchases further down the tree. However we do not have to
        // use coupons - it may be cheaper to buy an undiscounted item far
        // down the tree with a cheap base price than buying all the items
        // leading up to it just to get a discount that does not make up for
        // the cost of the path.
        F[u][i + k] = min(F[u][i + k], F[u][i] + min(F[v][k], G[v][k]));

        // If we cannot use a coupon this property holds for all remaining
        // items in this sub-tree.
        G[u][i + k] = min(G[u][i + k], G[u][i] + G[v][k]);
      }
    }

    S[u] += S[v];
  }
}

/**
 * Calculates the maximum number of items that Karen can buy.
 */
int items() {
  std::fill(&F[0][0], &F[0][0] + sizeof(F)/ sizeof(F[0][0]), INF);
  std::fill(&G[0][0], &G[0][0] + sizeof(G)/ sizeof(G[0][0]), INF);

  // Calculate F and G.
  dfs(0);

  // Find most items that can be bought with budget b in O(log N) time.
  int s = 0, lo = 0, hi = n;

  while (lo <= hi) {
    int m = lo + (hi - lo) / 2;

    // Slice search window in half.
    if (F[0][m] <= b || G[0][m] <= b) {
      s = m;
      lo = m + 1;
    } else {
      hi = m - 1;
    }
  }

  return s;
}

int main() {
  cin >> n >> b;

  assert(n <= MAX_N);

  cin >> C[0] >> D[0];
  for (int u = 1; u < n; u++) {
    cin >> C[u] >> D[u] >> X[u];
    X[u]--;
    T[X[u]].push_back(u);
  }

  cout << items() << endl;

  return 0;
}
