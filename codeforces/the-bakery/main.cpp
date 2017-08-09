#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr bool TEST = false;

constexpr int MAX_N = 35005;

constexpr int MAX_K = 55;

int n, k;

int A[MAX_N];

// DP[i][j] = Max value of packing the first i cakes in exactly j boxes.
int DP[MAX_N][MAX_K];

// P[i] = Last seen position of cakes i or 0 if not seen yet.
int P[MAX_N] = {0};

// T[i] = Max value at node i of the segment tree.
int T[MAX_N * 4] = {0};

// L[i] = Lazy incremental update at node i that we haven't propagated to
// leaves yet.
int L[MAX_N * 4] = {0};

//
// Pushes the lazy update value at this node to it's children.
//
void push(int node) {
  int l = node * 2 + 1;
  int r = node * 2 + 2;

  L[l] += L[node];
  L[r] += L[node];
  T[node] += L[node];
  L[node] = 0;
}

int rmq(int node, int lo, int hi, int i, int j) {
  if (j < lo || i > hi) {
    return 0;
  } else if (i <= lo && j >= hi) {
    // All elements under this node are in the query range. Don't forget the
    // lazy propagation!
    return T[node] + L[node];
  }

  // Split up query but don't forget to propagate the lazy update to children!
  push(node);
  int mid = lo + (hi - lo) / 2;
  return max(rmq(node * 2 + 1, lo, mid, i, j),
             rmq(node * 2 + 2, mid + 1, hi, i, j));
}

//
// Returns maximum value in range [i, j] of the segment tree in O(log n) time.
//
int rmq(int i, int j) {
  assert(i <= j && i >= 1 && j <= n);
  return rmq(0, 1, n, i, j);
}

void update(int node, int lo, int hi, int i, int j, int x) {
  if (j < lo || i > hi) {
    return;
  } else if (i <= lo && j >= hi) {
    // All elements under this node are in the query range. Use lazy
    // propagation during query time!
    L[node] += x;
  } else {
    // Split up query but don't forget to propagate the lazy update to children!
    push(node);

    int l = node * 2 + 1;
    int r = node * 2 + 2;

    int mid = lo + (hi - lo) / 2;
    update(l, lo, mid, i, j, x);
    update(r, mid + 1, hi, i, j, x);

    T[node] = max(T[l] + L[l], T[r] + L[r]);
  }
}

//
// Increments all values in  range [i, j] of the segment tree by x using lazy
// propagation in O(log n) time.
//
void update(int i, int j, int x) {
  assert(i <= j && i >= 1 && j <= n);
  update(0, 1, n, i, j, x);
}

//
// Clears T, L, (Segment Tree) and P.
//
void clear() {
  memset(T, 0, sizeof(T));
  memset(L, 0, sizeof(L));
  memset(P, 0, sizeof(P));
}

void test() {
  cout << "Begin basic tests..." << endl;

  n = 10;
  clear();
  assert(rmq(1, n) == 0);

  update(1, 10, 1);
  assert(rmq(1, 10) == 1);

  update(1, 5, 1);
  assert(rmq(1, 3) == 2);
  assert(rmq(2, 5) == 2);
  assert(rmq(3, 7) == 2);
  assert(rmq(6, 10) == 1);

  update(7, 10, 1);
  assert(rmq(1, 6) == 2);
  assert(rmq(6, 6) == 1);
  assert(rmq(7, 10) == 2);

  update(5, 8, 1);
  assert(rmq(1, 4) == 2);
  assert(rmq(5, 5) == 3);
  assert(rmq(6, 6) == 2);
  assert(rmq(7, 8) == 3);
  assert(rmq(9, 10) == 2);

  cout << "Begin stress tests..." << endl;

  n = MAX_N;
  clear();
  assert(rmq(1, n) == 0);

  srand(time(nullptr));
  vector<int> X(n + 1);

  for (int i = 0; i < 1000; i++) {
    int a = 1 + rand() % n;  // NOLINT
    int b = 1 + rand() % n;  // NOLINT
    if (b < a) swap(a, b);

    for (int j = a; j <= b; j++) X[j]++;
    update(a, b, 1);

    assert(*(max_element(X.data() + a, X.data() + b + 1)) == rmq(a, b));
  }

  cout << "Tests pass!" << endl;
}

int main() {
  ios::sync_with_stdio(false);

  if (TEST) test();

  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> A[i];

  // Fill in base case of DP with exactly one bucket.
  for (int i = 1; i <= n; i++) {
    DP[i][1] = P[A[i]] == 0 ? DP[i - 1][1] + 1 : DP[i - 1][1];
    P[A[i]] = i;
  }

  for (int j = 2; j <= k; j++) {
    clear();

    // Base case for this level - j buckets with 1 cake each.
    DP[j][j] = j;
    P[A[j]] = j;

    // Update the Segment Tree - each index m in the tree represents
    // DP[m][k - 1] + Unique(A[m + 1...i]).
    update(j - 1, j - 1, j);

    for (int i = j + 1; i <= n; i++) {
      // Update the Segment Tree - we increase indexes where A[i] is not in the
      // Unique(A[m + 1...i]) suffix. To do this we increase all indexes of the
      // tree after the last known occurence of A[i] using P[A[i]].
      int p = (P[A[i]] == 0) ? j - 1 : P[A[i]];
      if (p < i - 1) update(p, i - 2, 1);

      update(i - 1, i - 1, DP[i - 1][j - 1] + 1);
      DP[i][j] = rmq(j - 1, i);
      P[A[i]] = i;
    }
  }

  cout << DP[n][k] << endl;

  return 0;
}
