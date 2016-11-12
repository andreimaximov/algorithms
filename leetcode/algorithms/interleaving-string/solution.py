#!/usr/bin/env python


class Solution(object):
    def isInterleave(self, a, b, c):
        """
        Returns a boolean indicating if string c can be formed by interleaving
        strings a and b. Algorithm takes O(nm) time and space. This can be
        trivially optimized to O(min{n, m}) space because we are only reusing
        problems from the previous DP layer so we don not need to maintain an
        entire matrix. However this optimization has been left out for the sake
        of clarity.
        """
        n = len(a)
        m = len(b)

        if len(c) != n + m:
            return False
        elif n == 0:
            return c == b
        elif m == 0:
            return c == a

        # Each dp[i][j] represents isInterleaving(a[i:], b[j:], c[i + j:])
        dp = [[False for j in range(m + 1)] for i in range(n + 1)]

        # Base case for empty suffix of a, b, and c.
        dp[-1][-1] = True

        # Handle cases where we have used up all of b. Check if suffix of a
        # matches suffix of c.
        for i in range(n - 1, -1, -1):
            dp[i][m] = (a[i] == c[m + i]) and dp[i + 1][m]

        # Handle cases where we have used up all of a. Check if suffix of b
        # matches suffix of c.
        for j in range(m - 1, -1, -1):
            dp[n][j] = (b[j] == c[n + j]) and dp[n][j + 1]

        # Call A = a[i:], B = b[j:], and C = c[i + j:]. For each such A, B, and
        # C, C is an interleaving of A and B in two cases.
        #
        # 1) A[0] = C[0] and isInterleaving(A[1:], B, C[1:])
        # 2) B[0] = C[0] and isInterleaving(A, B[1:], C[1:])
        #
        # In either case, the first characer in C has to match either the first
        # character in A or B. Otherwuse there is no way to interleave A and B
        # to get C.
        for i in range(n - 1, -1, -1):
            for j in range(m - 1, -1, -1):
                k = i + j
                if a[i] == c[k] and dp[i + 1][j]:  # Case 1
                    dp[i][j] = True
                elif b[j] == c[k] and dp[i][j + 1]:  # Case 2
                    dp[i][j] = True

        return dp[0][0]


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/interleaving-string/')

if __name__ == '__main__':
    main()
