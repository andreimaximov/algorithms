#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::to_string;
using std::vector;
using std::tuple;
using std::make_tuple;
using std::get;

//
// Returns a {bulls, cows} result from guessing n.
//
tuple<int, int> guess(const string& n) {
  int bulls, cows;
  cout << n << endl << flush;
  cin >> bulls >> cows;
  return make_tuple(bulls, cows);
}

//
// Returns the set of at most 4 unique digits that make up the number we are
// trying to determine in at most 10 calls to guess(...).
//
vector<int> get_digits() {
  vector<int> digits;

  for (int digit = 0; digit < 10; digit++) {
    string query(4, '0' + digit);
    auto result = guess(query);

    int bulls = get<0>(result);
    int cows = get<1>(result);

    if (bulls + cows > 0) {
      digits.push_back(digit);
    }
  }

  return digits;
}

//
// Returns all combinations of counts that n unique digits can have to form a
// 4 digit number.
//
vector<vector<int>> get_counts(int n) {
  assert(n > 0);
  assert(n < 5);

  switch (n) {
    case 1: return {{4}};
    case 2: return {{2, 2}, {1, 3}, {3, 1}};
    case 3: return {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};
    case 4: return {{1, 1, 1, 1}};
  }

  return {};
}

//
// Guesses all permutations of the given digits and their counts until a valid
// arrangement is found or all permutations are exhausted. If n is the number
// of unique digits, we guarantee that this will take no more than 40 guesses.
//
// Case n = 1 -> 4! = 24 permutations
//
// Case n = 2 -> (4 * 3) / 2 + 2 * 4 = 14 permutations
//
// Case n = 3 -> 3 * (4 * 3) = 36 permutations
//
// Case n = 4 -> 1 permutation
//
// These permutations are derived from the possible count distributions of n
// unique digits forming a 4 digit number defined in the get_counts(...)
// function above.
//
bool dfs(const vector<int>& digits, vector<int>& counts, string n) {  // NOLINT
  // Check if the 4 digit number we have built up is valid.
  if (n.size() == 4) {
    auto result = guess(n);
    int bulls = get<0>(result);
    return bulls == 4;
  }

  // Append every digit with count > 0 to the current string and DFS.
  for (size_t i = 0; i < digits.size(); i++) {
    if (counts[i] > 0) {
      counts[i]--;
      bool found = dfs(digits, counts,  n + to_string(digits[i]));
      counts[i]++;
      if (found) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  auto digits = get_digits();

  for (auto counts : get_counts(digits.size())) {
    if (dfs(digits, counts, "")) {
      break;
    }
  }

  return 0;
}
