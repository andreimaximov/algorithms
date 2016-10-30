#!/usr/bin/env python


class Solution(object):
    def numDistinct(self, s, t):
        """
        Counts the number of distinct subequences of t in s.
        """
        n = len(s)
        m = len(t)
        if n == 0 or m == 0:
            return 0

        #
        # Setup the DP. Each entry dp[i][j] represents the number of distinct
        # subsequences of t[:i] in s[:j]. Each prefix of s has exactly one
        # distinct empty subsequence.
        #
        dp = [[0 for j in range(0, n + 1)] for i in range(0, m + 1)]
        for j in range(0, n + 1):
            dp[0][j] = 1

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                # Include the number of distinct t[:i] in s[:j - 1] in the
                # number of distinct t[:i] in s[:j].
                dp[i][j] = dp[i][j - 1]

                # If the last characters of each string match, also count the
                # number of distinct t[:i - 1] in s[:j - 1].
                if t[i - 1] == s[j - 1]:
                    dp[i][j] += dp[i - 1][j - 1]

        return dp[-1][-1]


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/distinct-subsequences/')

if __name__ == '__main__':
    main()
