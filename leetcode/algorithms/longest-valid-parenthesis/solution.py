#!/usr/bin/env python


class Solution(object):
    # 0 = stack, 1 = DP
    ALGO = 0

    def longestValidParentheses(self, s):
        """Returns the length of the longest valid parenthesis string in s."""
        if Solution.ALGO == 0:
            return self.longestValidParenthesesStack(s)
        return self.longestValidParenthesesDp(s)

    def longestValidParenthesesStack(self, s):
        """Returns the length of the longest valid parenthesis string in s.

        This a O(n) time and space algorithm that pairs up opening and closing
        parenthesis using a stack.
        """
        n = len(s)
        if n == 0:
            return 0

        stack = []
        longest = 0
        i = 0  # Start index of current window

        for j in xrange(n):
            if s[j] == '(':
                stack.append(j)
            else:
                if len(stack) == 0:
                    # Woops! Closing parenthesis without opening pair!
                    i = j + 1
                else:
                    # Pop corresponding opening parenthesis.
                    stack.pop()
                    if len(stack) == 0:
                        # We have closing/opening pairs for all of s[i...j].
                        longest = max(longest, j - i + 1)
                    else:
                        # We can guarantee that s[x + 1...j] is valid where x
                        # is the index of last unpaired opening parenthesis.
                        x = stack[-1]
                        longest = max(longest, j - x)

        return longest

    def longestValidParenthesesDp(self, s):
        """Returns the length of the longest valid parenthesis string in s.

        This is a O(n) time and space algorithm that uses DP.
        """
        n = len(s)
        if n < 2:
            return 0

        # Each dp[i] represents the longest valid parenthesis substring in
        # s[i...] starting at index i.
        dp = [0] * (n + 1)
        dp[n - 1] = 0
        dp[n - 2] = 2 if s[n - 2] == '(' and s[n - 1] == ')' else 0

        for i in xrange(n - 3, -1, -1):
            if s[i] == ')':
                # Cannot begin valid string with closing parenthesis.
                continue
            elif s[i + 1] == '(':
                # In this case we are trying to find a valid parenthesis
                # substring (x)y starting at i where len(x) = dp[i + 1] and
                # len(y) = dp[j + 1].
                j = i + dp[i + 1] + 1
                if j < n and s[j] == ')':
                    dp[i] = 2 + dp[i + 1] + dp[j + 1]
            elif s[i + 1] == ')':
                # In this case we are trying to find a valid parenthesis
                # substring ()x where len(x) = dp[i + 2].
                j = i + dp[i + 2] + 1
                dp[i] = 2 + dp[i + 2]

        return max(dp)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/longest-valid-parentheses/')

if __name__ == '__main__':
    main()
