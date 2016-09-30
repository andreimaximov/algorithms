#!/usr/bin/env python


class Solution(object):
    def isMatch(self, s, p):
        """
        Returns a boolean indicating if the pattern p matches string s. See
        LeetCode problem description for full pattern spec.
        """
        n = len(s)
        m = len(p)

        # If the pattern has more non-star chars than s has total chars, there
        # is no way we can match the pattern even if we ignore all stars.'
        if (m - p.count('*') > n):
            return False

        # Each lastDP[i] represents isMatch(s[:i], p[:j]) for previous j. We do
        # not need a full 2D matrix since the recursive relation only depends
        # on a sub-problem that is one level lower.
        lastDP = [False] * (n + 1)
        lastDP[0] = True

        for j in range(1, m + 1):
            # Create DP for the current j.
            nextDP = [False] * (n + 1)

            # Empty s matches p prefix if prefix contains only *'s.
            nextDP[0] = lastDP[0] and p[j - 1] == '*'

            for i in range(1, n + 1):
                if p[j - 1] == '*':
                    # Skip * or current character.
                    nextDP[i] = lastDP[i] or nextDP[i - 1]
                elif p[j - 1] == '?':
                    # Skip current character and ?.
                    nextDP[i] = lastDP[i - 1]
                else:
                    # Ensure characters match and that s[:i] matches p[:j].
                    nextDP[i] = (s[i - 1] == p[j - 1]) and \
                            lastDP[i - 1]
            lastDP = nextDP
        return lastDP[-1]


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/wildcard-matching/')

if __name__ == '__main__':
    main()
