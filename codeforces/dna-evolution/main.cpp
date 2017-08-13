#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr bool TESTS = false;

// Maximum length of the original string.
constexpr int MAX_S = 100000;

// Maximum length of each infection string. Determines how many offsets and
// periods we need to store in T.
constexpr int MAX_E = 10;

// For each character E[i] we want to ask: How many times does E[i] occur in
// S[l...r] with offset (l + i) % |E| and period |E|?
//
// To make this possible we make T[c][o][p] a bit mask where T[c][o][p][e] is 1
// if S[i] = c and S[i] has offset, period = o, p. Otherwise the entry is 0.
// This bit mask can be represented with a Binary Index Tree for O(log MAX_S)
// point updates and range sums.
int T[4][MAX_E][MAX_E + 1][MAX_S + 1] = {0};

// Original string.
string S;

int chr(char c) {
  switch (c) {
    case 'A': return 0;
    case 'T': return 1;
    case 'G': return 2;
    case 'C': return 3;
    default: assert(false);
  }
}

//
// Updates index i in BIT T[c][o][p] by x.
//
void update(int c, int o, int p, int i, int x) {
  assert(i >= 0 && i < MAX_S);

  i++;

  while (i <= MAX_S) {
    T[c][o][p][i] += x;
    i += (i & -i);
  }
}

//
// Updates all BIT's for S[i] by x in O(log MAX_S) time.
//
void update(int i, int x) {
  int c = chr(S[i]);

  for (int p = 1; p <= MAX_E; p++) {
    for (int o = 0; o < p && o <= i; o++) {
      if ((i - o) % p == 0) {
        update(c, o, p, i, x);
      }
    }
  }
}

//
// Prefix Sum Query on first i elements of T[c][o][p].
//
int psq(int c, int o, int p, int i) {
  assert(o >= 0 && o < p && p <= MAX_E);
  assert(i >= 0 && i <= MAX_S);

  int s = 0;

  while (i > 0) {
    s += T[c][o][p][i];
    i -= (i & -i);
  }

  return s;
}

//
// Range Sum Query on range [l, r] of T[c][o][p].
//
int rsq(int c, int o, int p, int l, int r) {
  return psq(c, o, p, r + 1) - psq(c, o, p, l);
}

//
// Populates T to reflect the initial state of string S.
//
void preprocess() {
  assert(!S.empty());
  assert(S.size() <= MAX_S);

  memset(T, 0, sizeof(T));

  int n = S.size();
  for (int i = 0; i < n; i++) {
    update(i, 1);
  }
}

void test() {
  cout << "Begin basic tests..." << endl;

  S = "ATGCATGC";
  preprocess();

  assert(rsq(chr('A'), 0, 1, 0, 7) == 2);
  assert(rsq(chr('T'), 0, 1, 0, 7) == 2);
  assert(rsq(chr('G'), 0, 1, 0, 7) == 2);
  assert(rsq(chr('C'), 0, 1, 0, 7) == 2);

  assert(rsq(chr('A'), 0, 4, 0, 7) == 2);
  assert(rsq(chr('T'), 1, 4, 0, 7) == 2);
  assert(rsq(chr('G'), 2, 4, 0, 7) == 2);
  assert(rsq(chr('C'), 3, 4, 0, 7) == 2);

  assert(rsq(chr('A'), 1, 3, 0, 2) == 0);
  assert(rsq(chr('A'), 1, 3, 3, 7) == 1);
  assert(rsq(chr('A'), 1, 3, 0, 7) == 1);
  assert(rsq(chr('T'), 1, 2, 0, 7) == 2);

  update(3, -1);
  S[3] = 'T';
  update(3, 1);

  assert(rsq(chr('A'), 0, 2, 1, 5) == 1);
  assert(rsq(chr('T'), 1, 2, 1, 5) == 3);

  cout << "Tests pass!" << endl;
}

int main() {
  ios::sync_with_stdio(false);

  if (TESTS) test();

  cin >> S;
  preprocess();

  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    int t;
    cin >> t;

    if (t == 1) {
      int x;
      char c;
      cin >> x >> c;

      update(x - 1, -1);
      S[x - 1] = c;
      update(x - 1, 1);
    } else if (t == 2) {
      int l, r;
      string E;
      cin >> l >> r >> E;

      int n = E.size(), v = 0;

      for (int j = 0; j < n; j++) {
        int k = chr(E[j]);
        int o = (l + j - 1) % n;
        v += rsq(k, o, n, l - 1, r - 1);
      }

      cout << v << endl;
    }
  }

  return 0;
}
