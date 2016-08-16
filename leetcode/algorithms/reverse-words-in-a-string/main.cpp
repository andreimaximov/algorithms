#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

class Solution {
 public:
  //
  // Reverses the words in a string in place in O(1) space and O(N^2) time.
  //
  // A very simple O(N) space solution can be created using a std::stringstream
  // and pre-pending each token i to the reversed string of tokens 0 to i - 1.
  // However that is still an O(N^2) algorithm.
  //
  void reverseWords(std::string &s) { // NOLINT
    size_t i = 0;  // The current index we are at.
    int lastEnd = -2;  // The end index of the last word.

    while (i < s.size()) {
      if (s[i] == ' ') {
        // Skip whitespace.
        i++;
      } else {
        // Reverse the word we just encountered.
        size_t end = nextEndOfWord(s, i);
        std::reverse(&s[i], &s[end] + 1);

        // Shift left such that there is exactly once space between this
        // word and the previous word.
        int shift = i - lastEnd - 2;
        if (shift > 0) {
          std::copy(&s[i], &s[end] + 1, &s[i] - shift);

          // Fill up space after shifted word but before next word with spaces.
          std::fill(&s[end] + 1 - shift, &s[end] + 1, ' ');
        }

        lastEnd = end - shift;
        i = lastEnd + 1;
      }
    }

    // If original string was all whitespace, assign an empty string.
    if (lastEnd == -2) {
        s = "";
        return;
    }

    // Copy up till last character of last word to trim trailing whitespace.
    s = std::string(&s[0], &s[lastEnd] + 1);

    // Reverse entire string.
    std::reverse(s.begin(), s.end());
  }

 private:
  //
  // Returns the index of the last character in a word beginning at index i.
  //
  size_t nextEndOfWord(const std::string &s, size_t i) {
    while (i < s.size()) {
      if (s[i] == ' ') {
        break;
      }
      i++;
    }
    return i - 1;
  }
};

void test(std::string input, const std::string output, size_t i) {
  std::cout << "Running test " << i << "..." << std::endl;
  Solution sol;
  sol.reverseWords(input);
  assert(input == output);
}

int main() {
  test("", "", 1);
  test(" ", "", 2);
  test(" ab cde ", "cde ab", 3);
  return 0;
}
