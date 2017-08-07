#include <bits/stdc++.h>

using namespace std;  // NOLINT

#define LINEAR_ALGO

constexpr int MAX_N = 200005;

int N;

// A[i] = Height of ith bear.
int A[MAX_N];

#ifndef LINEAR_ALGO

// LEFT[i] = Set ID to the left of set i or -1 if such a set does not exist.
int LEFT[MAX_N];

// Same as above, but for right side.
int RIGHT[MAX_N];

// SIZE[i] = Number of bears in set/group i.
int SIZE[MAX_N];

// STRENGTH[i] = Stength of bear group/set i.
int STRENGTH[MAX_N];

// MERGES = Set of (s, i, j) tuples where s is the strength of group after
// merging groups i and j. Initially this is contains all pairs of adjacent
// bears.
set<tuple<int, int, int>, greater<tuple<int, int, int>>> MERGES;

//
// High level idea: Maintain a set of merge candidates and greedily merge
// groups into larger groups with the highest strength.
//
void solve() {
  // Preprocess.
  LEFT[0] = -1;
  for (int i = 1; i < N; i++) LEFT[i] = i - 1;

  RIGHT[N - 1] = -1;
  for (int i = 0; i < N - 1; i++) RIGHT[i] = i + 1;

  for (int i = 0; i < N; i++) {
    SIZE[i] = 1;
    STRENGTH[i] = A[i];
  }

  // Populate MERGE with initial set of merge candidates. (Single bear groups)
  for (int i = 0; i < N - 1; i++) {
    int s = min(A[i], A[i + 1]);
    MERGES.emplace(s, i, i + 1);
  }

  // Calculate base case of x = 1.
  cout << *(max_element(A, A + N)) << " ";

  int x = 2;
  while (x < N + 1) {
    assert(!MERGES.empty());

    auto it = MERGES.begin();
    int s, i, j;
    tie(s, i, j) = *it;
    MERGES.erase(it);

    // Clear merge candidate with i as right group and j as left group before
    // performing merge.
    if (LEFT[i] != -1) {
      auto key = make_tuple(min(STRENGTH[i], STRENGTH[LEFT[i]]), LEFT[i], i);
      MERGES.erase(key);
    }

    if (RIGHT[j] != -1) {
      auto key = make_tuple(min(STRENGTH[j], STRENGTH[RIGHT[j]]), j, RIGHT[j]);
      MERGES.erase(key);
    }

    // Now we perform the merge.
    RIGHT[i] = RIGHT[j];
    if (RIGHT[i] != -1) LEFT[RIGHT[i]] = i;

    SIZE[i] += SIZE[j];
    STRENGTH[i] = s;

    // s is now the highest strength for groups of size x ... SIZE[i].
    while (x <= SIZE[i]) {
      cout << s << " ";
      x++;
    }

    // Insert updates left/right candidates we erased earlier.
    if (LEFT[i] != -1) {
      auto key = make_tuple(min(STRENGTH[LEFT[i]], s), LEFT[i], i);
      MERGES.insert(key);
    }

    if (RIGHT[i] != -1) {
      auto key = make_tuple(min(s, STRENGTH[RIGHT[i]]), i, RIGHT[i]);
      MERGES.insert(key);
    }
  }

  cout << endl;
}

#else

// LEFT[i] = Largest j < i such that A[j] < A[i] or -1 if DNE.
int LEFT[MAX_N];

// RIGHT[i] = Smallest j > i such that A[j] < A[i] or -1 if DNE.
int RIGHT[MAX_N];

// STRENGTH[i] = The greatest strength of a group of size i. If STRENGHT[i] is
// 0 then we inherit group strength from the next known size. This is because
// if STRENGTH[i] = k then STRENGTH[j] >= k for all j < i.
int STRENGTH[MAX_N];

//
// Calculates LT such that LT[i] = Largest index in A less than i such that
// A[LT[i]] < A[i].
//
void closest_less_than(int * LT) {
  LT[0] = -1;
  stack<int> candidates;
  candidates.push(0);

  for (int i = 1; i < N; i++) {
    while (!candidates.empty() && A[candidates.top()] >= A[i]) {
      candidates.pop();
    }
    LT[i] = candidates.empty() ? -1 : candidates.top();
    candidates.push(i);
  }
}

void solve() {
  // Preprocess.
  for (int i = 1; i <= N; i ++) STRENGTH[i] = 0;

  closest_less_than(LEFT);
  reverse(A, A + N);

  closest_less_than(RIGHT);
  reverse(A, A + N);
  reverse(RIGHT, RIGHT + N);

  for (int i = 0; i < N; i++) {
    RIGHT[i] = N - 1 - RIGHT[i];
  }

  for (int i = 0; i < N; i++) {
    int size = RIGHT[i] - LEFT[i] - 1;
    STRENGTH[size] = max(STRENGTH[size], A[i]);
  }

  // Sanity check.
  assert(STRENGTH[N] > 0);

  int i = N;

  // Iterate from end and fill in STRENGTH. We know that if STRENGTH[i] = k
  // then STRENGTH[j] >= k for all j < i but we may have broken this so lets
  // fix it.
  for (int x = N - 1; x > 0; x--) {
    STRENGTH[x] = max(STRENGTH[x], STRENGTH[i]);
    if (STRENGTH[x] > STRENGTH[i]) {
      i = x;
    }
  }

  for (int x = 1; x <= N; x++) cout << STRENGTH[x] << " ";
  cout << endl;
}

#endif

int main() {
  ios::sync_with_stdio(false);

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  solve();

  return 0;
}
