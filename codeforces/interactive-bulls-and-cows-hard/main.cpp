//
// Solution largely inspired by discussion at
// http://codeforces.com/blog/entry/49635.
//

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>

using std::string;
using std::set;
using std::vector;

//
// Represents the result of a guess.
//
struct result {
  int bulls = 0;

  int cows = 0;

  bool operator==(const result& other) {
    return other.bulls == bulls && other.cows == cows;
  }
};


//
// Returns a {bulls, cows} result from guessing n.
//
result guess(const string& n) {
  result r;
  std::cout << n << std::endl;
  std::cin >> r.bulls >> r.cows;
  return r;
}

//
// Returns the {bulls, cows} result between x and y.
//
result diff(const string& x, const string& y) {
  assert(x.size() == y.size());

  result r;
  for (size_t i = 0; i < x.size(); i++) {
    if (x[i] == y[i]) {
      r.bulls++;
    } else if (x.find(y[i]) != string::npos) {
      r.cows++;
    }
  }
  return r;
}

//
// Computes the best guess that is guaranteed to eliminate the most numbers in
// the worst case using min-max technique.
//
string choose_best_guess(const vector<string>& left,
                         const vector<string>& all) {
  string best_guess;
  int left_count = left.size() + 1;

  // Count the highest number of possible candidates left after each guess.
  for (const string& guess : all) {
    // Tracks the number of candidates left for each {bulls, cows} result class
    // after applying guess as a filter on each candidates.
    vector<vector<int>> counts(5, vector<int>(5, 0));

    for (const string& other : left) {
      result r = diff(guess, other);
      counts[r.bulls][r.cows]++;
    }

    // We now have a matrix of the counts of numbers that match guess for each
    // {bulls, cows} combination. In reality, the candidates left after each
    // guess will be counts[bulls][cows] but we do not know what the result of
    // the guess is yet. Thus we assume the worst case and use the largest
    // count which trims the candidate set the least. This is the essence of
    // the min-max algorithm.
    //
    int guess_left_count = 0;
    for (int bulls = 0; bulls < 5; bulls++) {
      for (int cows = 0; cows < 5; cows++) {
        guess_left_count = std::max(guess_left_count, counts[bulls][cows]);
      }
    }

    if (guess_left_count < left_count) {
      best_guess = guess;
      left_count = guess_left_count;
    }
  }

  return best_guess;
}

//
// Performs a guess n, and returns a filtered copy of candidates with the only
// possible candidates that match the result of guessing n.
//
vector<string> filter(const string& n, const vector<string>& left) {
  result r = guess(n);

  vector<string> filtered;
  auto inserter = std::back_inserter(filtered);

  auto matcher = [n, r](const string& other) {
    return diff(n, other) == r;
  };

  copy_if(left.begin(), left.end(), inserter, matcher);
  return filtered;
}

int main() {
  // Generate a pool of candidate (permutations) that the number we are looking
  // for could be.
  vector<string> all;
  set<int> digits;

  for (int n = 0; n < 10000; n++) {
    int a = n % 10;
    int b = (n / 10) % 10;
    int c = (n / 100) % 10;
    int d = (n / 1000) % 10;
    if (a == b || a == c || a == d || b == c || b == d || c == d) {
      continue;
    }

    // 0-pad and add as candidate.
    string s = std::to_string(n);
    s = string(4 - s.size(), '0') + s;
    all.push_back(s);
  }

  vector<string> left(all);

  while (left.size() > 1) {
    string guess = choose_best_guess(left, all);
    left = filter(guess, left);
  }

  if (left.size() == 1) {
    std::cout << left[0] << std::endl;
  }

  return 0;
}
