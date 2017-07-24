#include <bits/stdc++.h>

using namespace std;  // NOLINT

constexpr int MAX_N = 100000;

constexpr bool RUN_TESTS = false;

int N;

//
// Fenwick Tree representing the number of remaining cards in A.
//
int T[MAX_N + 10] = {0};

//
// Increments the value for cards i in the Fenwick Tree.
//
void update(int i, int x) {
  assert(i >= 0 && i < N);

  i++;
  while (i <= N) {
    T[i] += x;
    i += (i & -i);
  }
}

//
// Counts the number of cards in A[0...i - 1] that remain.
//
int count(int i) {
  assert(i >= 0 && i <= N);

  int s = 0;

  while (i > 0) {
    s += T[i];
    i -= (i & -i);
  }

  return s;
}

//
// Counts the number of cards in A[i...j - 1] that remain.
//
int range(int i, int j) {
  assert(i >= 0 && i <= N);
  assert(j >= i && j <= N);

  return count(j) - count(i);
}

void test() {
  cout << "Running tests..." << endl;

  N = 4;

  assert(range(0, 4) == 0);

  update(0, 1);
  update(1, 1);
  update(3, 1);

  assert(range(0, 1) == 1);
  assert(range(0, 2) == 2);
  assert(range(0, 4) == 3);

  std::fill(&T[0], &T[0] + sizeof(T) / sizeof(T[0]), 0);
  assert(range(0, N) == 0);

  cout << "Tests pass!" << endl;
}

//
// Returns the index in indices that is closest to the right of i. If no such
// index exists the search "loops" back to i = 0 and continues.
//
int get_closest(int i, const std::set<int>& indices) {
  assert(!indices.empty());

  auto it = indices.lower_bound(i);

  if (it != indices.end()) {
    return *it;
  }

  return *indices.begin();
}

int main() {
  if (RUN_TESTS) {
    test();
  }

  cin >> N;

  // Ordered mapping from number to the set of card indices with the number.
  std::map<int, std::set<int>> index;

  for (int i = 0; i < N; i++) {
    int a;
    cin >> a;

    // Indicate that this card is currently in the set of unsorted cards.
    update(i, 1);
    index[a].insert(i);
  }

  // The values in index sorted in reverse order by key. This ensures we can
  // access and pop the set of indices corresponding to the smallest number in
  // our current stack in O(1) time.
  std::stack<std::set<int>> cards;
  for (auto it = index.rbegin(); it != index.rend(); ++it) {
    cards.push(std::move(it->second));
  }

  // The index in A of the card currently at the top of the stack.
  int offset = 0;

  // The number of cards Vasily has taken from the top of the stack.
  int64_t pops = 0;

  while (!cards.empty()) {
    // Get the closest index of the smallest card value.
    auto& indices = cards.top();
    int i = get_closest(offset, indices);

    if (indices.size() == 1) {
      cards.pop();
    } else {
      indices.erase(i);
    }

    // Pop everything still in the stack between the minimum card and the
    // offset.
    if (offset <= i) {
      pops += range(offset, i + 1);
    } else {
      pops += count(i + 1) + range(offset, N);
    }

    offset = (i + 1) % N;

    // Remove the minimum card from the stack.
    update(i, -1);
  }

  cout << pops << endl;

  return 0;
}

