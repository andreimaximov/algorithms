#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr int MAX_N = 200000;

/**
 * The number of bids.
 */
int N;

/**
 * Each S[i] is an ordered list of (j, k) pairs for person i. In each (j, k)
 * pair k is the number of bids person i made on and after the j-th bid. The
 * j's in each S[i] should be stored in increasing order.
 */
std::vector<pair<int, int>> S[MAX_N];

/**
 * Stores the person of each bid.
 */
int A[MAX_N];

/**
 * Stores the size of each bid.
 */
int B[MAX_N];

/**
 * Stores the people to exclude from the bidding sequence during a query.
 */
std::vector<int> L;

/**
 * Counts the number of bids people in L made after the i-th bid in
 * O(|L| log N) time.
 */
int after(int i) {
  int count = 0;

  for (int a : L) {
    auto it = upper_bound(S[a].begin(), S[a].end(), make_pair(i, MAX_N + 1));
    if (it != S[a].end()) {
      count += it->second;
    }
  }

  return count;
}

/**
 * Returns the index of the winning bid after removing people in L from the
 * auction in O(|L| log N) time. Returns -1 if there is no winning bid -
 * happens if L contains all original bidders.
 */
int query() {
  int l = 0;
  int r = N - 1;
  int k = -1;  // Index of winning bid.

  // Binary search to find the last bid that can be a winner - even if it's
  // the same person out-bidding themselves. A winning bid is one that (1) not
  // by someone in L (excluded from the auction) and (2) has no other bids
  // after it by people not excluded from the auction.
  while (l <= r && k == -1) {
    int m = l + (r - l) / 2;

    // Count the number of binds by people excluded from the auction after m.
    int count = after(m);
    assert(count <= N - 1 - m);

    // The number of original bids after m is N - 1 - m. Use this to check
    // if there are any bids after m by someone not excluded from the auction -
    // even if that bidder (unknown) is the same person as bidder of bid m.
    if (count < N - 1 - m) {
      l = m + 1;
    } else if (binary_search(L.begin(), L.end(), A[m])) {
      // Every bid after and including m is by an excluded person.
      r = m - 1;
    } else {
      k = m;
    }
  }

  if (k != -1) {
    // Now we need to handle the case where after removal of all people in L,
    // it looks like bidder of bid k was out-bidding himself.
    int a = A[k];
    assert(k == S[a].rbegin()->first);

    int l = 0;
    int r = S[a].size() - 1;

    // We handle this by binary searching through their bids in O(log N) time.
    while (l <= r) {
      int m = l + (r - l) / 2;
      int i = S[a][m].first;

      // Check if there is someone besides bidder a who placed a bid after bid
      // i. The number of bids by people not excluded from the auction after
      // bid i is (N - 1 - i) - after(i). We check if this value is greater
      // than the number of bids placed by bidder a after bid i.
      if (after(i) + S[a][m].second - 1 < N - 1 - i) {
        // Whoa! Someone excluded from the auction placed a bid after us.
        l = m + 1;
      } else {
        // i is a winning bid, but maybe not the smallest one so keep looking.
        k = i;
        r = m - 1;
      }
    }
  }

  return k;
}

int main() {
  int a, b, q, k;

  // Parse input.
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    a--;

    S[a].emplace_back(i, 0);
    A[i] = a;
    B[i] = b;
  }

  // Build index S - see declaration at top for info.
  for (int a = 0; a < N; a++) {
    int count = 0;
    for (auto it = S[a].rbegin(); it != S[a].rend(); ++it) {
      count++;
      it->second = count;
    }
  }

  cin >> q;

  for (int i = 0; i < q; i++) {
    // Fill L with people to exclude from auction.
    cin >> k;
    L.resize(k);

    for (int j = 0; j < k; j++) {
      cin >> L[j];
      L[j]--;
    }

    sort(L.begin(), L.end());

    // Query.
    int k = query();

    if (k != -1) {
      // Note: Using 0-indexed bids and people.
      cout << (A[k] + 1) << " " << B[k] << endl;
    } else {
      cout << "0 0" << endl;
    }
  }

  return 0;
}

