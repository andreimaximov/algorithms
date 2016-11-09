#!/usr/bin/env python


class Solution(object):
    def wordBreak(self, word, dictionary):
        """
        Checks if the word can be broken up into words from the specified
        dictionary.

        :type word: str
        :type dictionary: List[str]
        :rtype: bool
        """
        n = len(word)
        if n == 0 or len(dictionary) == 0:
            return False

        # Turn the dictionary into a set for ~O(1) lookup.
        dictionary = set(dictionary)

        # Each dp[i] indicates if we can word break word[:i]
        dp = [False] * (n + 1)
        dp[0] = True

        # word[:i] can be broken up if (1) there exists a j such that word[:j]
        # can be broken up and suffix word[j:i] is in the dictionary or (2)
        # word[:i] is in the dictionary.
        for i in range(1, n + 1):
            # Find a prefix word[:j] that can be broken up. This includes the
            # empty string to handle case 2.
            for j in range(0, i):
                if not dp[j]:
                    continue
                suffix = word[j:i]
                if suffix in dictionary:
                    dp[i] = True
                    break

        return dp[-1]


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/word-break/')

if __name__ == '__main__':
    main()
