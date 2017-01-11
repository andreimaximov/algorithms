#include <bits/stdc++.h>

using namespace std;  // NOLINT

//
// Represents an inclusive range of integers in [lo, hi].
//
struct range {
  int lo;

  int hi;

  int i;

  int size() {
    return hi - lo + 1;
  }

  //
  // Order by lo and break ties with hi.
  //
  bool operator<(const range& other) const {
    if (lo < other.lo) {
      return true;
    } else if (lo > other.lo) {
      return false;
    }
    return hi < other.hi;
  }
};


int main() {
  size_t n, k;
  cin >> n >> k;

  vector<range> coupons(n);

  for (size_t i = 0; i < n; i++) {
    cin >> coupons[i].lo >> coupons[i].hi;
    coupons[i].i = i + 1;
  }

  // Sort the coupons by lower bound.
  sort(coupons.begin(), coupons.end());

  // The range of product ID's that our best choices of k coupons can cover.
  range biggest {0, -1};

  // Holds upper bounds of current coupon set. Lowest upper bound is at top.
  priority_queue<int, vector<int>, greater<int>> upper;

  for (const range& coupon : coupons) {
    upper.push(coupon.hi);

    // If we have k coupons selected -> 1) Check if the range of the current
    // set is wider than the current best and 2) Pop off the lowest upper bound
    // so that we can potentially replace it with a higher upper bound.
    if (upper.size() == k) {
      // coupon.lo is the lower bound of the current range since we sorted by
      // lo and coupon.lo >= other.lo for all other coupons in the current set.
      range candidate {coupon.lo, upper.top()};
      if (candidate.size() > biggest.size()) {
        biggest = candidate;
      }
      upper.pop();
    }
  }

  cout << biggest.size() << endl;

  if (biggest.size() == 0) {
    // There are not k coupons that overlap at all so we can select any k and
    // we are guaranteed that at least 2 in our selection will not overlap.
    for (size_t i = 1; i <= k; i++) {
      cout << i << " ";
    }
  } else {
    // Select k coupons that completely fit the best range.
    for (size_t i = 0; i < n && k > 0; i++) {
      if (coupons[i].lo <= biggest.lo && coupons[i].hi >= biggest.hi) {
        cout << coupons[i].i << " ";
        k--;
      }
    }
  }

  cout << endl;
  return 0;
}

