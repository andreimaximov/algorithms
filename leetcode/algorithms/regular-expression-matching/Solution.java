//
// Checks if a string s matches regular expression p.
//
// See https://leetcode.com/problems/regular-expression-matching/ for complete
// problem description.
//
// The idea is that for any s and p we can split the problem into the following
// cases.
//
// 1. s[-1:] == p[-1:] or p[-1:] == . -> Recurse on s[:-1] and p[:-1]
//
// 2. s[-1:] != p[-1:] and p[-1:] == '*' ->
//    a. If s[-1:] != p[-2:-1] -> Recurse on s[:] and p[:-2]. (Ignoring
//                                trailing char* on p)
//    b. Else if s[-1:] == p[-2:-1] -> Recurse such that we:
//       i.   Ignore trailing x* on p
//       ii.  Count trailing x* on p exactly one
//       iii. Count trailing x* on p more than once
//
//  We also need to be careful for regular expressions with unmatched prefixes
//  that can be safely ignored. For example, a*b*c matches c because the
//  beginning a*b* can be ignored due to the * quantifiers.
//
public class Solution {
  //
  // Flag to control algorithm use.
  //
  public static final boolean USE_DP_ALGORITHM = true;

  public boolean isMatch(String s, String p) {
    if (USE_DP_ALGORITHM) {
      return isMatchDP(s.toCharArray(), p.toCharArray());
    } else {
      return isMatchRecursive(s, s.length() - 1, p, p.length() - 1);
    }
  }

  //
  // Dynammic programming implementation.
  //
  public boolean isMatchDP(char[] s, char[] p) {
    // Check for illegal starting quantifier.
    if (p.length > 0 && p[0] == '*') {
      return false;
    }

    // Continue with DP
    boolean[][] dp = new boolean[s.length + 1][p.length + 1];

    // Base case
    // All dp[i][0] remain false
    dp[0][0] = true;

    // Calculate all dp[0][j] because it might be okay to have handing prefix
    // on p if and only if the extra prefix is a reocurring x* pattern because
    // each x* can be safely ignored.
    //
    // For example, a*b*c matches c because the beginning a*b* can be ignored
    // due to the * quantifiers.
    for (int j = 1; j < p.length; j++) {
      if (p[j] == '*') { //
        dp[0][j + 1] = dp[0][j - 1];
      }
    }

    // Run DP
    for (int i = 0; i < s.length; i++) {
      for (int j = 0; j < p.length; j++) {
        if (s[i] == p[j] || p[j] == '.') { // s = ?x, p = ?y or s = ?x, p = ?.
          dp[i + 1][j + 1] = dp[i][j];
        } else if (p[j] == '*') {
          if (s[i] != p[j - 1] && p[j - 1] != '.') { // s = ?x, p = ?y*
            dp[i + 1][j + 1] = dp[i + 1][j - 1]; // Ignore trailing y* on p
          } else { // s = ?x, p = ?x* or s = ?x, p = ?.*
            dp[i + 1][j + 1] = dp[i + 1][j - 1] || // Ignore trailing x* or .*
                dp[i + 1][j] || // Match exactly one x or .
                dp[i][j + 1]; // Match more than one x or .
          }
        }
      }
    }

    return dp[s.length][p.length];
  }

  //
  // Recursive implementation.
  //
  public boolean isMatchRecursive(String s, int i, String p, int j) {
    // Base cases
    if (i < 0 && j < 0) {
      // Entire regex matched entire string!
      return true;
    } else if (i < 0 && j >= 0) {
      // Check if we have a dangling prefix pattern of x* that can be ignored.
      // See DP algorithm for more detailed explanation.
      if (p.charAt(j) == '*' && j > 0) { // s = , p = ?x*
        return isMatchRecursive(s, i, p, j - 2); // Ignore x*
      } else {
        return false; // Either x*... pattern does not exist or illegal * at
                      // start of regex.
      }
    } else if (i >= 0 && j < 0) {
      // Part of string did not match regex.
      return false;
    }

    // Recursion
    if (s.charAt(i) == p.charAt(j) || p.charAt(j) == '.') { // s = ?x, p = ?x or s = ?x, p = ?.
      return isMatchRecursive(s, i - 1, p, j - 1);
    } else if (p.charAt(j) == '*') {
      if (j == 0) {
        return false; // Check for illegal starting *
                      // (Quantifier without a character before it)
      } else if (s.charAt(i) != p.charAt(j - 1) && p.charAt(j - 1) != '.') { // s = ?x, p = ?y* and y != .
        return isMatchRecursive(s, i, p, j - 2); // Ignore y* on p
      } else { // s = ?x, p = ?x* or s = ?x, p = ?.*
        return isMatchRecursive(s, i, p, j - 2) || // Ignore x* or .*
            isMatchRecursive(s, i, p, j - 1) || // Count single x
            isMatchRecursive(s, i - 1, p, j); // Count more than 1 x
      }
    }

    // Does not match
    return false;
  }

  public static void main(String[] args) {
    System.out.println("Please run this solution on LeetCode.");
    System.out.println("https://leetcode.com/problems/regular-expression-matching/");

    Solution solution = new Solution();

    assert !solution.isMatch("aa", "a");
    assert solution.isMatch("aa", "aa");
    assert !solution.isMatch("aaa", "aa");
    assert solution.isMatch("aa", "a*");
    assert solution.isMatch("aa", ".*");
    assert solution.isMatch("ab", ".*");
    assert solution.isMatch("aab", "c*a*b");
    assert !solution.isMatch("a", ".*..a*");
    assert solution.isMatch("aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s");

    System.out.println("Tests pass!");
  }
}