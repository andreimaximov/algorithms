#!/usr/bin/env python


class Solution(object):
    def minDistance(self, a, b):
        """
        Returns the edit distance between strings a and b.
        """
        n = len(a)
        m = len(b)

        # If either string is empty, we need to add all characters from other
        # string.
        if n == 0 or m == 0:
            return max(n, m)

        # n x m matrix where each dp[i][j] represents the edit distance for
        # a[:i + 1] and b[:j + 1].
        dp = [([0] * (m + 1)) for i in range(0, n + 1)]

        for i in range(0, n + 1):
            for j in range(0, m + 1):
                if i == 0:
                    dp[i][j] = j
                elif j == 0:
                    dp[i][j] = i
                elif a[i - 1] == b[j - 1]:
                    # If the trailing characters are the same, we don't need to
                    # perform an operation to bring these characters in sync.
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    dp[i][j] = 1 + \
                            min(dp[i - 1][j - 1],  # Replace a[i] with b[j]
                                dp[i][j - 1],  # Add a[i] to b[:j] (Insert)
                                dp[i - 1][j])  # Add b[j] to a[:i] (Delete)

        return dp[n][m]


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/edit-distance/')

if __name__ == '__main__':
    main()
