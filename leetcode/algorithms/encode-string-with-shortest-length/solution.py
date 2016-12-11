#!/usr/bin/env python


class Solution(object):
    def encode(self, s):
        """Encodes a string with the shortest possible length in O(n^3) time.

        See problem description for encoding rules.
        """
        n = len(s)

        # Create an index where all O(n^2) possible substrings begin.
        index = dict()
        for i in range(n):
            for j in range(i, n):
                x = s[i:j + 1]
                if x not in index:
                    index[x] = set()
                index[x].add(i)

        # Each dp[i][j] reperesents the shortest encoding for s[i:j + 1].
        dp = [[None for _ in range(n)] for _ in range(n)]
        return self.encodeUtil(s, 0, n - 1, index, dp)

    def encodeUtil(self, s, i, j, index, dp):
        """Calculates the shortest encoding for s[i:j + 1].

        There are O(n^2) subproblems but each subproblem considers O(n) smaller
        subproblems so the overall runtime is O(n^3)."""
        n = j - i + 1
        if n < 5:
            # Cannot compress anything shorter than 5 characters.
            return s[i:j + 1]
        elif dp[i][j] is not None:
            return dp[i][j]

        # Default encoding is just the raw string.
        encoding = s[i:j + 1]

        # Consider all repeating prefix substrings.
        for k in range(i, j):
            # Count how many times x occurs back to back in s[i:j + 1].
            x = s[i:k + 1]
            count = 1
            start = i + len(x)
            while start in index[x]:
                count += 1
                start += len(x)

            # Compress the prefix.
            x = self.encodeUtil(s, i, k, index, dp)
            if count > 1:
                prefix = '%d[%s]' % (count, x)
            else:
                prefix = x

            # Compress the suffix.
            suffix = self.encodeUtil(s, start, j, index, dp)

            # Apply prefix and suffix if encoding with x as prefix is shorter.
            if len(prefix) + len(suffix) < len(encoding):
                encoding = prefix + suffix

        dp[i][j] = encoding
        return encoding


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/contest/leetcode-weekly-contest-12/problems/encode-string-with-shortest-length/')  # nopep8

if __name__ == '__main__':
    main()
