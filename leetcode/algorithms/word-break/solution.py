#!/usr/bin/env python

import bisect


class Solution(object):
    def _find(self, array, value):
        """
        Returns the index of the first occurence of value in array. The array
        is expected to be sorted. Returns -1 if the value does not exist.
        """
        i = bisect.bisect_left(array, value)
        if i != len(array) and array[i] == value:
            return i
        return -1

    def _wordBreak(self, word, i, dictionary, cache):
        """
        Checks if word[i:] can be broken up into words from the specified
        dictionary. Uses a list to cache results for all i from 0 to
        len(word) - 1.
        """
        assert i >= 0
        assert i < len(word)

        # Check if we have solved this problem before.
        if cache[i] is not None:
            return cache[i]

        # Check if the sub-string we are operating on (word[i:]) is in the
        # dictionary.
        full = word[i:]
        if self._find(dictionary, full) != -1:
            cache[i] = True
            return True

        # If the entire word[i:] sub-string is not in the dictionary, check if
        # any of it's prefixes are and if the suffix after each such prefix
        # can be broken down into words from the dictionary.
        cache[i] = False
        for j in range(i, len(word) - 1):
            prefix = word[i:j + 1]
            # Check if the prefix  is in the dictionary.
            if self._find(dictionary, prefix) != -1:
                # If the prefix is in the dictionary, check if the remaining
                # suffix can be broken down into words.
                if self._wordBreak(word, j + 1, dictionary, cache):
                    cache[i] = True
                    break

        return cache[i]

    def wordBreak(self, word, dictionary):
        """
        Checks if the word can be broken up into words from the specified
        dictionary.

        :type word: str
        :type dictionary: List[str]
        :rtype: bool
        """
        if len(word) == 0 or len(dictionary) == 0:
            return False

        dictionary = list(sorted(dictionary))
        cache = [None] * len(word)
        return self._wordBreak(word, 0, dictionary, cache)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/word-break/')

if __name__ == '__main__':
    main()
