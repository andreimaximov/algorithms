#!/usr/bin/env python


class Solution(object):
    def _count(self, values):
        """
        Returns a dictionary of counts for each value in the list.

        :type values: List[T]
        :rtype: Dict[T, int]
        """
        counts = dict()
        for v in values:
            if v not in counts:
                counts[v] = 0
            counts[v] += 1
        return counts

    def _findSubstring(self, string, i, counts, k):
        """
        Finds all starting indices of substrings that are a concatenation of
        each word in counts starting at index i. This function examines words
        in offsets of k from i. Runs in O(N) time where N is the length of the
        string. (Examines at most N/K words each of length K)

        The idea behind the algorithm is to keep track of a window of
        consecutive words. Each new word following the window falls into one of
        3 cases.

        i) Not in the dictionary of words we are allowed to use.
        ii) Allowed and available.
        iii) Allowed but not available.

        :type string: str
        :type i: int
        :type counts: Dict[str, int] The dictionary and counts of words we are
                                     allowed to use.
        :type k: int The length of each word.i
        :rype: List[int]
        """
        # Total numbers of words that we need to use.
        total = sum(counts.values())

        # Tracks count of each word in current window.
        current = {w: 0 for w in counts}

        # The start index of the current window.
        start = i

        # The number of words left that we stil need to use.
        left = total

        indices = []
        n = len(string)

        while i < n - k + 1:
            word = string[i:i + k]

            if word not in counts:
                # This is not a usable word so there is no way a substring can
                # contain it. Restart the window after this word to skip it.
                current = {w: 0 for w in counts}
                start = i + k
                left = total
                i += k

            elif current[word] < counts[word]:
                # This word is allowed and available so use it.
                current[word] += 1
                left -= 1
                if left == 0:
                    # If we have used all the words save the start as a valid
                    # substring start index.
                    indices.append(start)
                    # Slide the start to the right to free the first word.
                    first = string[start:start + k]
                    current[first] -= 1
                    start += k
                    left += 1
                # Continue on to the next word.
                i += k

            else:
                # This word is allowed but not available. Slide the window
                # start forward until this word becomes available again.
                while start <= i and current[word] == counts[word]:
                    discard = string[start:start + k]
                    current[discard] -= 1
                    start += k
                    left += 1

        return indices

    def findSubstring(self, string, words):
        """
        Finds all starting indices of substrings in string that are a
        concatenation of each word in words exactly once and without any gaps.
        If N is the length of the string, and K is the length of each word, the
        algorithm runs in O(NK) time.

        :type string: str
        :type words: List[str] The set of words we need to consecutively use in
                               each valid substring.
        :rtype: List[int]
        """
        n = len(string)
        m = len(words)
        if n == 0 or m == 0:
            return []

        k = len(words[0])
        if k == 0 or k > n:
            return []
        counts = self._count(words)
        indices = []
        for i in range(0, k):
            indices += self._findSubstring(string, i, counts, k)
        return indices


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/substring-with-concatenation-of-all-words/')  # nopep8

if __name__ == '__main__':
    main()
