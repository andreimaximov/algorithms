#!/usr/bin/env python


class Solution(object):
    def encode(self, s):
        """Encodes a string with the shortest possible length in O(n^3) time.

        See problem description for encoding rules.
        """
        n = len(s)

        # Each dp[i][j] reperesents the shortest encoding for s[i:j + 1].
        dp = [[None for _ in range(n)] for _ in range(n)]
        return self.encodeUtil(s, 0, n - 1, dp)

    def encodeUtil(self, s, i, j, dp):
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
        k = i
        while k < j:
            # Count how many times x occurs back to back in s[i:j + 1].
            x = s[i:k + 1]
            y = self.encodeUtil(s, i, k, dp)
            count = 0
            start = i

            while s[start:start + len(x)] == x:
                count += 1
                start += len(x)

                # Compress the prefix.
                prefix = y if count == 1 else '%d[%s]' % (count, y)

                # Compress the suffix.
                suffix = self.encodeUtil(s, start, j, dp)

                # Apply if encoding with x as prefix is shorter.
                if len(prefix) + len(suffix) < len(encoding):
                    encoding = prefix + suffix

            # This is critical for speedup! Essentially if we have a prefix x
            # that repeats p times, we do not need to consider any prefixes
            # formed by repeating x p times. Why? Because without this we will
            # be performing unecessary (repeat) calls to get optimal suffix.
            k = i + len(x) * count

        dp[i][j] = encoding
        return encoding


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/contest/leetcode-weekly-contest-12/problems/encode-string-with-shortest-length/')  # nopep8

if __name__ == '__main__':
    main()
