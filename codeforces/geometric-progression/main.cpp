#include <bits/stdc++.h>

using namespace std;  // NOLINT

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}

//
// Calculates min(i^p, ceil)
//
int ipow(int i, int p, int ceil = numeric_limits<int>::max()) {
  if (p == 0) {
    return 1;
  } else if (p % 2 == 1) {
    return i * ipow(i, p - 1);
  }
  int y = ipow(i, p / 2);
  int64_t g = static_cast<int64_t>(y) * y;
  if (g > ceil) {
    return ceil;
  }
  return g;
}

//
// The editorial at http://codeforces.com/blog/entry/49880 does a good job
// explaining the optimal solution but I have included my explanation as well.
//
// Define a(i) as the ith term of the sequence.
//
// A geometric sequence is defined by (1) a(1) and (2) d the ratio between
// terms. For any sequence that we wish to include in our count, the following
// conditions must hold.
//
// 1) a(1) >= l
//
// 2) a(n) = a(1) * d^(n - 1) <= r
//
// We will count increasing sequences so d > 1. What is the upper bound of d?
// Well, the lower bound of (a) is 1 so d^(n - 1) <= r so d <= r^(1 / (n - 1)).
//
// The strategy is to go through all integers 1 < d <= r^(1 / (n - 1)) and
// count the number of sequences matching conditions (1) and (2) for each d.
//
// Every d must be rational and so can be represented by integers x and y such
// that d = x / y where x > y since d > 1. Thus
// a(n) = a(1) * (x^(n - 1)) / (y^( n - 1 )). Here's the trick I was not able
// to come up with myself - We can say b = a(1) / (y^(n - 1)) and rewrite the
// sequence conditions like so.
//
// 1) a(1) = b * y^(n - 1) >= l
//
// 2) a(n) = b * x^(n - 1) <= r
//
// From this we can say that (3) l / (y^(n - 1)) <= b <= r / (x^(n - 1)). Since
// b is a function of a(1), y, and n, we can count the number of unique b's
// in range (3) for any y and n!
//
// But how many x and y pairs are there? Well we derived d <= r^(1 / (n - 1))
// so x / y <= r^(1 / ( n - 1 )) -> (4) x, y <= r^(1 / (n - 1)). We simply
// loop through all such pairs x, y where x > y and count the number of b's
// using equation (3)!
//
// Lastly, we have only counted the number of increasing sequence where d > 1.
// Fortunately there is exactly one decreasing sequence with d' = 1 / d for
// each increasing sequence so we double our final count.
//
// Done!
//
int main() {
  int n, l, r;
  cin >> n >> l >> r;

  if (n == 1) {
    // Special case
    cout << r - l + 1 << endl;
    return 0;
  } else if (n == 2) {
    // This loop below will work but will run in O(r^2 log r) time because
    // the upper bound of ration d will be r! Instead just count up all unique
    // pairs.
    int64_t k = r - l + 1;
    cout << k * (k - 1) << endl;
    return 0;
  }

  int64_t count = 0;

  for (int x = 1; x <= r; x++) {
    // Check upper bound of d.
    if (ipow(x, n - 1) > r) {
      break;
    }

    for (int y = 1; y < x; y++) {
      // If gcd(x, y) != 1 then we have already encountered x', y', c such that
      // x = cx' and y = cy'. This implies that we have already counted all b's
      // for the ratio d = x /y = cx' / cy' = d' so we do not need to count
      // them again.
      if (gcd(x, y) == 1) {
        count += max(r / ipow(x, n - 1) - (l - 1) / ipow(y, n - 1), 0);
      }
    }
  }

  // Each increasing sequence has a matching decreasing sequence
  cout << count * 2 << endl;

  return 0;
}

