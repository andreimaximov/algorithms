#!/usr/bin/env python


class Solution(object):
    def encode(self, s):
        """Encodes a string with the shortest possible length in O(n^3) time.

        See problem description for encoding rules. Credit to Stefan Pochmann
        for finding optimal repeating prefix substring. See his original
        solution at https://discuss.leetcode.com/topic/71442/short-python.
        """
        n = len(s)

        # Each dp[x] represents the shortest encoding for a substring x of s.
        dp = dict()
        return self.encodeUtil(s, dp)

    def encodeUtil(self, s, dp):
        """Calculates the shortest encoding for s.

        There are O(n^2) subproblems but each subproblem considers O(n) smaller
        subproblems so the overall runtime is O(n^3)."""
        n = len(s)
        if n < 5:
            # Cannot compress anything shorter than 5 characters.
            return s
        elif s in dp:
            return dp[s]

        # Encode the string raw by default.
        encoding = s

        # Encode the string as the shortest repeating substring if possible.
        i = (s + s).find(s, 1)

        # Check if a repeating substring exists and it is not s.
        if i != -1 and i < n:
            repeat = s[:i]
            count = n / len(repeat)
            encoding = '%d[%s]' % (count, self.encodeUtil(repeat, dp))

        # Now consider all possible splits between chars 0 through n - 1.
        for i in range(1, n):
            left = self.encodeUtil(s[:i], dp)
            right = self.encodeUtil(s[i:], dp)
            if len(left) + len(right) < len(encoding):
                encoding = left + right

        dp[s] = encoding
        return encoding


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/contest/leetcode-weekly-contest-12/problems/encode-string-with-shortest-length/')  # nopep8

if __name__ == '__main__':
    main()
