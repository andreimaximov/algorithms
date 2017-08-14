#include <bits/stdc++.h>

using namespace std;  // NOLINT

// The maximum number of bits we need to represent positions 1 ... n.
constexpr int MAX_BITS = 10;

int n, x, y;

//
// Queries the XOR of icicles with positions idxs.
//
int query(const vector<int>& idxs) {
  cout << "? " << idxs.size();
  for (int i : idxs)
    cout << " " << i;
  cout << endl << flush;

  int z;
  cin >> z;
  assert(z != -1);

  return z;
}

//
// Finds the position of a single special icicle in positions idxs.
//
int find_one(const vector<int>& idxs) {
  assert(!idxs.empty());

  if (idxs.size() == 1) return idxs[0];

  auto mid = idxs.begin() + idxs.size() / 2;
  vector<int> left(idxs.begin(), mid);

  int z = query(left);

  if ((left.size() % 2 == 0 && z != 0) || (left.size() % 2 == 1 && z == y))
    return find_one(left);

  vector<int> right(mid, idxs.end());
  return find_one(right);
}

//
// Returns a set of positions with the i'th bit set to 1.
//
vector<int> idxs_with_bit(int i) {
  vector<int> idxs;
  int mask = 1 << i;

  for (int p = 1; p <= n; p++)
    if ((mask & p) != 0)
      idxs.push_back(p);

  return idxs;
}

//
// Returns the bits that the positions of the two special icicles differ in.
//
vector<int> find_diff_bits() {
  vector<int> diff;

  for (int i = 1; i <= MAX_BITS; i++) {
    auto idxs = idxs_with_bit(i - 1);

    if (idxs.empty()) continue;

    auto z = query(idxs);

    if ((idxs.size() % 2 == 0 && z != 0) || (idxs.size() % 2 == 1 && z == y))
      diff.push_back(i - 1);
  }

  return diff;
}

int main() {
  ios::sync_with_stdio(false);

  cin >> n >> x >> y;

  // 1. Find bits in positions of special icicles that are different.
  auto bits = find_diff_bits();
  assert(!bits.empty());

  // 2. Search for single special icicle in a set of positions where a
  // differing bit is on. This way we guarantee only one special icicle in the
  // set.
  auto idxs = idxs_with_bit(bits[0]);
  int p = find_one(idxs);

  // 3. Reconstruct the other icicle using the bits we know are different.
  int q = p;
  for (int i : bits) {
    // Clear the ith bit of q.
    q = q & ~(1 << i);

    // Set to inverse of ith bit of p.
    if ((p & (1 << i)) == 0) q = q | (1 << i);
  }

  if (p > q) swap(p, q);

  cout << "! " << p << " " << q << endl;

  return 0;
}
