#include <iostream>
#include <string>
#include <vector>
#include <cassert>

class Solution {
 public:
  std::string shortestPalindrome(const std::string &source) {
    if (source.size() == 0) {
      return "";
    }

    //
    // Prepare to solve this problem with the KMP algorithm. The source string
    // can be broken into S = P + T where P is the longest palindrome at the
    // start of the source string and T is the remaining tail.
    //
    // If F' = reverse(F) then D = S + # + S' = (P + T) + # + (T' + P). We
    // can run KMP on string D to find the longest prefix which is also a
    // suffix. This will be P!
    //
    // Once we find P we can easily derive T and return T' + P + T which will
    // be the shortest palindrome we can construct by appending characters to
    // the source string.
    //
    std::string reverse(source.rbegin(), source.rend());
    std::string input = source + '#' + reverse;
    std::vector<size_t> table = kmp(input);

    // Get T.
    size_t p_length = table[table.size() - 1];
    std::string tail(source.begin() + p_length, source.end());

    // Create the resulting shortest palindrome.
    std::string prefix(tail.rbegin(), tail.rend());
    return prefix + source;
  }

 private:
  //
  // Uses a Knuth–Morris–Pratt algorithm table to find the longest prefix of
  // the string that is also a suffix. See the following link for an
  // explanation for how the table works.
  //
  // http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
  //
  std::vector<size_t> kmp(const std::string &source) {
    size_t n = source.size();
    std::vector<size_t> table(n);

    // Track the last index in the prefix that we need to check if it matches
    // with the last index in the suffix.
    size_t prefix_index = 0;

    // Go through all sub-strings source[0:suffix_index + 1] and find the
    // longest prefix that is also a prefix for each.
    for (size_t suffix_index = 1; suffix_index < n; suffix_index++) {
      if (source[prefix_index] == source[suffix_index]) {
        // Last characters of prefix and suffix match so just increment length
        // of previous sub-string solution!
        table[suffix_index] = table[suffix_index - 1] + 1;
        prefix_index++;
      } else {
        // Last characters of prefix and suffix do not match. What we need to
        // do is find the longest prefix that is both (1) a suffix of the
        // previous sub-string and (2) is followed by the last character of
        // the current sub-string which is denoted by source[suffix_index].

        // Index of the character after the longest prefix that is a suffix of
        // the previous sub-string.
        prefix_index = table[suffix_index - 1];

        // Continue until we find a prefix that matches our conditions or no
        // such prefix exists.
        while (prefix_index > 0 &&
               source[prefix_index] != source[suffix_index]) {
          // At the beginning of this loop iteration we are guaranteed that
          // source[0:prefix_index + 1] is a prefix and suffix of the previous
          // sub-string. Resolving this problem for source[0:prefix_index]
          // maintains this loop invariant.
          prefix_index = table[prefix_index - 1];
        }

        // Check if condition (2) has been met. If so advance the prefix index.
        if (source[prefix_index] == source[suffix_index]) {
          prefix_index++;
        }

        // Save the result for sub-string source[0:suffix_index + 1].
        table[suffix_index] = prefix_index;
      }
    }

    return table;
  }
};

//
// Delete before submitting to LeetCode.
//
int main() {
  Solution sol;
  assert(sol.shortestPalindrome("") == "");
  assert(sol.shortestPalindrome("cba") == "abcba");
  assert(sol.shortestPalindrome("cbabcde") == "edcbabcde");
  assert(sol.shortestPalindrome("abcd") == "dcbabcd");
  assert(sol.shortestPalindrome("aabbaad") == "daabbaad");
}
