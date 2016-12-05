#!/usr/bin/env python


class Solution(object):
    def alpha(self, c):
        """Returns the index of char c in the alphabet."""
        return ord(c) - ord('a')

    def findSubstringInWraproundString(self, p):
        """Counts the unique substrings of p in the infinite wraparound string.

        This is an O(n) time and space DP algorithm.

        Args:
            p (str): The string whos substrings we are considering.

        Returns:
            (int)
        """
        n = len(p)
        if n == 0 or n == 1:
            return n

        # Create a DP array that tracks the length of the longest alphabetic
        # substring starting at char c we have considered thus far.
        chars = set(p)
        dp = {c: 0 for c in chars}

        i = 0
        count = 0

        # Loop through p and find chunks of alphabetic substrings.
        while i < n:
            # Find the endpoint of the current alphabetic window substring
            # starting at index i.
            j = i + 1
            while j < n and \
                    self.alpha(p[j]) == (self.alpha(p[j - 1]) + 1) % 26:
                j += 1

            # Treat each k as a substring starting point.
            for k in xrange(i, j):
                c = p[k]
                length = j - k

                # We may have counted substrings starting with c before so
                # count only the longer ones we have not considered yet.
                endpoints = max(0, length - dp[c])
                count += endpoints

                # Update the longest substring starting with c we have counted.
                dp[c] = max(dp[c], length)

            # Start looking for next alphabetic window at j.
            i = j

        return count


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/unique-substrings-in-wraparound-string/')  # nopep8

if __name__ == '__main__':
    main()
