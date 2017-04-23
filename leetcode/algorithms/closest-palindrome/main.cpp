#include <iostream>
#include <string>
#include <cassert>


using std::string;
using std::to_string;
using std::cout;
using std::endl;


class Solution {
 public:
  string nearestPalindromic(string x) {
    int64_t y = stoll(x);
    if (y < 0) {
      return "0";
    } else if (y == 0) {
      return "1";
    }
    return to_string(nearest(y));
  }

  int64_t nearest(int64_t x) {
    assert(x >= 0);

    int64_t a = bigger(x + 1);
    int64_t b = smaller(x - 1);

    assert(a > x);
    assert(b < x);

    if (a - x < x - b) {
      return a;
    } else {
      return b;
    }
  }

  //
  // Returns the closest palindromic number that is greater than or equal to x.
  //
  int64_t bigger(int64_t x) {
    assert(x >= 0);

    string s = to_string(x);
    int n = s.size();

    // Base case, we just take the lower digits and replace them with the
    // reversed upper digits to create some sort of palindrome that may be <,
    // =, or > the original x. This means that the left half of p and s,
    // including the center for odd length cases, are always identical.
    string p = s;
    for (int i = 0; i < n / 2; i++) {
      p[n - 1 - i] = p[i];
    }

    // Go through right half of the palindrome and make sure that p >= x.
    for (int i = n / 2; i < n; i++) {
      if (s[i] > p[i]) {
        // Whoa! s[i] > p[i] so p < x. We will propagate from the center of p
        // and try to increment each digit for the smallest change to p such
        // that p >= x. Propagating from the center results in the smallest
        // change because incrementing a lower place digit on the right of p
        // requires an update to its reflection on the left, a higher place
        // digit, to maintain p as a palindrome.
        for (int j = (n - 1) / 2; j >= 0; j--) {
          p[j]++;
          if (p[j] > '9') {
            // Carry a 1 over to the next higher place digit to the left just
            // like in basic math.
            p[j] = '0';
          } else {
            // No 1 to carry over! We know that s[0...j - 1] == p[0...j - 1]
            // since the left half of s and p are initially identical. Thus
            // after this increment s[0...j] < p[0...j] so s < p.
            break;
          }
        }

        // Update to ensure p is a palindrome.
        for (int i = 0; i < n / 2; i++) {
          p[n - 1 - i] = p[i];
        }

        return stoll(p);
      } else if (s[i] < p[i]) {
        // If s[i] < p[i] then p > x.
        return stoll(p);
      }
    }

    return stoll(p);
  }

  //
  // Returns the closest palindromic number that is less than or equal to x.
  // This is similar to the bigger(x) function with a minor edge case
  // difference. (See comments)
  //
  int64_t smaller(int64_t x) {
    assert(x >= 0);

    if (x < 10) {
      return x;  // Handle single digit cases
    }

    string s = to_string(x);
    int n = s.size();

    string p = s;
    for (int i = 0; i < n / 2; i++) {
      p[n - 1 - i] = p[i];
    }

    for (int i = n / 2; i < n; i++) {
      if (s[i] < p[i]) {
        for (int j = (n - 1) / 2; j >= 0; j--) {
          p[j]--;
          if (p[j] < '0') {
            p[j] = '9';
          } else {
            break;
          }
        }

        // This is different from the bigger(x) function. We might run into a
        // case like this. Say s = 1000 and p = 1001 initially so we end up
        // with p = 0901 -> p = 0990 after mirroring. This isn't a valid number
        // so we replace such cases with 999... (one less digit than x) because
        // a 0 in the left most digit indicates we did not have enough to
        // "borrow" when decrementing.
        if (p[0] == '0') {
          p = string(n - 1, '9');
          return stoll(p);
        }

        for (int i = 0; i < n / 2; i++) {
          p[n - 1 - i] = p[i];
        }

        return stoll(p);
      } else if (s[i] > p[i]) {
        return stoll(p);
      }
    }

    return stoll(p);
  }
};

//
// Delete before submitting to LeetCode.
//
int main() {
  cout << "Please run this solution on LeetCode." << endl;
  cout << "https://leetcode.com/contest/leetcode-weekly-contest-29/problems/find-the-closest-palindrome/" << endl;  // NOLINT
  return 0;
}
