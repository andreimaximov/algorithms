#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr bool TEST = false;

constexpr int MAX_N = 1000000;

constexpr int OFFSET = MAX_N;

/**
 * DIFFS[OFFSET + k] is the number of indexes i in P such that
 * P[i] - i - 1 = k. There is another separate zero offset term we use which
 * explained in the solve(...) function.
 */
int64_t DIFFS[3 * MAX_N] = {0};

int64_t P[MAX_N];

int N;

struct Shift {
  int64_t dev;

  int i;
};

/**
 * Finds the shift with minimal deviation in O(n) time and space.
 */
Shift solve() {
  Shift shift {0, 0};

  // Tracks the number of negative and positive P[i] - i - 1 terms in the
  // current permutation.
  int pos = 0, neg = 0;

  // Calculate the deviation for unshifted P and use it as the base case.
  for (int i = 0; i < N; i++) {
    auto k = P[i] - i - 1;

    shift.dev += abs(k);
    DIFFS[OFFSET + k]++;

    if (k > 0) {
      pos++;
    } else if (k < 0) {
      neg++;
    }
  }

  assert(pos + neg + DIFFS[OFFSET] == N);

  auto prev = shift.dev;

  for (int s = 1; s < N; s++) {
    // Use previous deviation as base.
    auto curr = prev;

    // This is the other previous mentioned offset. (Details lower)
    int zero = s - 1;

    // Temporarily exclude the last element of the previous permutation.
    auto a = P[N - s] - N;
    DIFFS[MAX_N + zero + a]--;

    if (a > 0) {
      pos--;
    } else if (a < 0) {
      neg--;
    }

    curr -= abs(a);

    // Now shift the first N - 1 elements of the previous permutation 1
    // position to the right. Elements with 0 or negative diffs increase
    // in absolute value difference while positive diffs decrease in absolute
    // value difference since the amount we are subtracting from each element
    // increases by one.
    curr += DIFFS[MAX_N + zero] + neg - pos;

    // Update the positive/negative counts.
    neg += DIFFS[MAX_N + zero];
    pos -= DIFFS[MAX_N + zero + 1];

    // Now move the last element of previous permutation to front. Note that
    // the zero index is one greater. This is how we efficiently shift all
    // the keys in DIFF down by one - just increase zero by one!
    auto b = P[N - s] - 1;
    DIFFS[b + MAX_N + zero + 1]++;

    if (b > 0) {
      pos++;
    } else if (b < 0) {
      neg++;
    }

    curr += abs(b);

    if (curr < shift.dev) {
      shift.dev = curr;
      shift.i = s;
    }

    prev = curr;
  }

  return shift;
}

/**
 * Calculates the deviation of P right-shifted s positions.
 */
int64_t dev(int s) {
  int64_t dev = 0;

  for (int i = 0; i < N; i++) {
    dev += abs(P[(N + i - s) % N] - i - 1);
  }

  return dev;
}

/**
 * Naively finds the shift with minimal deviation as a reference.
 */
Shift reference() {
  Shift shift {dev(0), 0};

  for (int s = 1; s < N; s++) {
    auto d = dev(s);
    if (d < shift.dev) {
      shift.dev = d;
      shift.i = s;
    }
  }

  return shift;
}

void test() {
  cout << "Testing..." << endl;

  srand(time(0));

  N = 1000;

  for (int t = 0; t < 100; t++) {
    for (int i = 0; i < N; i++) {
      P[i] = rand() % N;  // NOLINT
    }
  }

  auto a = solve(), e = reference();

  assert(a.dev == e.dev);
  assert(a.i == e.i);

  cout << "Tests pass!" << endl;
}

int main() {
  if (TEST) {
    test();
  }

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> P[i];
  }

  auto shift = solve();
  cout << shift.dev << " " << shift.i << endl;

  return 0;
}
