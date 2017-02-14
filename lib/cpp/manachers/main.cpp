#include <vector>
#include <string>
#include <cassert>
#include <iostream>

//
// Returns a table P where each P[i] indicates the length of the longest
// palindrome centerted around the character at index i.
//
std::vector<size_t> manachers(const std::string& str) {
  std::vector<size_t> P(str.size(), 0);

  size_t r = 0;  // Right bound
  size_t c = 0;  // Center of palindrome

  for (size_t i = 1; i < str.size() - 1; i++) {
    // Reflection of i around the center of the current palindrome.
    size_t j = 2 * c - i;

    if (r > i) {
      // Be careful if mirror j of i expands past left side of current
      // palindrome centered at c! We will manually check and expand edges to
      // ensure correctness.
      P[i] = std::min(P[j], r - i);
    }

    // If r > i, then P[i] is positive but it may be possible to expand if
    // mirror j of i expands past left side of current palindrome. We could
    // also be in the case where i > r so we need to recalculate the palindrome
    // centered at i from scratch.
    while (i + 1 + P[i] < str.size() &&
           i >= 1 + P[i] &&
           str[i + 1 + P[i]] == str[i - 1 - P[i]]) {
      P[i]++;
    }

    // Check if the right bound should be expanded. If so, update left, right,
    // and center of current palindrome with the one centered at i.
    if (i + P[i] > r) {
      r = i + P[i];
      c = i;
    }
  }

  return P;
}

//
// Returns the longest palindrome in string str.
//
std::string longest_palindrome(const std::string& str, char separator = '#') {
  // Separate characters in string with a unique character to elegantly handle
  // even and odd length palindrome in Manacher's.
  std::vector<char> chars(str.size() * 2 + 1);
  chars[0] = separator;
  for (size_t i = 0; i < str.size(); i++) {
    chars[2 * i + 1] = str[i];
    chars[2 * i + 2] = separator;
  }

  // Build palindrome length table of longest palindrome centered at each
  // index.
  std::vector<size_t> P = manachers(std::string(chars.begin(), chars.end()));

  size_t center = 0;
  size_t length = 0;

  for (size_t i = 0; i < P.size(); i++) {
    if (P[i] > length) {
      center = i;
      length = P[i];
    }
  }

  // Extract longest palindrome.
  std::string result;
  if (center % 2 == 1) {
    assert(length % 2 == 1);
    result = str.substr((center - length) / 2, length);
  } else {
    assert(length % 2 == 0);
    result = str.substr((center - length) / 2, length);
  }

  return result;
}

int main() {
  assert(longest_palindrome("") == "");
  assert(longest_palindrome("a") == "a");
  assert(longest_palindrome("aa") == "aa");
  assert(longest_palindrome("454abcba121") == "abcba");
  assert(longest_palindrome("aba1234321bcdedcb") == "1234321");

  std::cout << "Tests pass!" << std::endl;

  return 0;
}

