#!/usr/bin/env python


class Solution(object):
    def _isPalindrome(self, word, start, end):
        """
        Checks if the word between indices start and end inclusive is a
        palindrome.

        :type word: str
        :type start: int
        :type end: int
        :rtype: bool
        """
        assert word is not None
        assert start >= 0 and start < len(word)
        assert end >= 0 and end < len(word)
        l = start
        r = end
        while l < r:
            if word[l] != word[r]:
                return False
            l += 1
            r -= 1
        return True

    def _buildSuffixesPrefixes(self, words):
        """
        Builds two dictionaries A and B where A is the prefix dictionary and B
        is the suffix dictionary.

        For each prefix P in each word W, A has the key P if there is an X such
        that P + X = W and X is a palindrome. For each suffix S in each word W,
        B has they key S if there is a Y such that Y + S = W and Y is a
        palindrome.

        The value corresponding to each key K is the list of indices
        corresponding to words in the original array where K is either a prefix
        or suffix.

        Takes O(N * K^2) time where N is the number of words and K is the
        average length of a word.

        :type words: List[str]
        :rtype: (Dict[str, List[int]], Dict[str, List[int]])
        """
        n = len(words)
        prefixes = {words[i]: [i] for i in range(0, n)}
        suffixes = {words[i]: [i] for i in range(0, n)}

        for i in range(0, n):
            word = words[i]
            k = len(word)
            for j in range(0, k):
                # Check if word after prefix is a palindrome
                if self._isPalindrome(word, j, k - 1):
                    pre = word[0:j]
                    if pre not in prefixes:
                        prefixes[pre] = list()
                    prefixes[pre].append(i)
                # Check if word before suffix is a palindrome
                if self._isPalindrome(word, 0, j):
                    suff = word[j + 1:k]
                    if suff not in suffixes:
                        suffixes[suff] = list()
                    suffixes[suff].append(i)

        return (prefixes, suffixes)

    def _gather(self, graph, words):
        """
        Gathers a set of edges (i, j) where i != j and graph is either the
        prefix (A) or suffix (B) array from buildSuffixesPrefixes(...).

        :type graph: Dict[str, List[str]]
        :type words: List[str]
        :rtype: Set[(int, int)]
        """
        pairs = set()
        for i in range(0, len(words)):
            rword = words[i][::-1]
            if rword in graph:
                for j in graph[rword]:
                    if i != j:
                        pairs.add((i, j))
        return pairs

    def palindromePairs(self, words):
        """
        Finds all pairs (i, j) where i != j and words[i] + words[j] is a
        palindrome.

        Let's call words[i] L and words[j] R. L + R is a palindrome in the
        following two cases.

        1. R = X + reverse(L) where X is a palindrome -> reverse(R) = L + X
        2. L = reverse(R) + Y where Y is a palindrome -> reverse(L) = Y + R

        To efficiently finds pairs L and R, we can build a prefix and suffix
        array such that for each word W in words we check for a mapping from
        reverse(W) to an L + X or Y + R as described above.

        The runtime of the algorithm is O(N * K^2) where N is the number of
        words and K is the average word length.

        :type words: List[str]
        :rtype: List[List[int]]
        """
        (prefixes, suffixes) = self._buildSuffixesPrefixes(words)

        # Flip each tuple since each word is really a suffix of the candidate
        # palindrome.
        lhs = map(lambda pair: (pair[1], pair[0]),
                  self._gather(prefixes, words))
        rhs = self._gather(suffixes, words)

        return list(set(lhs) | rhs)


def test(input, expect, i):
    print('Running test %d...' % i)
    sol = Solution()
    expect = set([tuple(pair) for pair in expect])
    actual = sol.palindromePairs(input)
    actual = set([tuple(pair) for pair in actual])
    try:
        assert actual == expect
    except AssertionError:
        print('Actual %s but expected %s!' % (actual, expect))
        raise


def main():
    test([], [], 1)
    test(['a', ''], [[0, 1], [1, 0]], 2)
    test(['abcd', 'dcba', 'lls', 's', 'sssll'],
         [[0, 1], [1, 0], [3, 2], [2, 4]], 3)
    print('Tests pass!')
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/palindrome-pairs/')


if __name__ == "__main__":
    main()
