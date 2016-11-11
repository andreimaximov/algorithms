#!/usr/bin/env python


class Solution(object):
    def wiggleMaxLength(self, values):
        """
        Returns the maximum length of a wiggle subsequence. The problem boils
        down to finding the number of min/max inflection points in the
        sequence. For example, if we are looking for an "up" wiggle in the
        sequence it makes sense to go as high up as we can to increase the set
        of numbers that will allow us to come back in a "down" wiggle. Similar
        logic holds when going "down" the wiggle.

        LeetCode has an excellent article about this problem:
        https://leetcode.com/articles/wiggle-subsequence/

        :type values: List[int]
        :rtype int
        """
        n = len(values)
        if n < 2:
            return n

        i = 0

        # Find the starting direction of the wiggle sequence.
        while i < n - 1:
            if values[i] != values[i + 1]:
                direction = values[i + 1] - values[i]
                break
            i += 1

        # All values are the same!
        if i == n - 1:
            return 1

        # Calculate the length of the wiggle sequence.
        last = values[0]
        length = 2
        while i < n:
            if (values[i] - last) * direction < 0:
                direction *= -1
                length += 1
            last = values[i]
            i += 1
        return length


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/non-overlapping-intervals/')

if __name__ == '__main__':
    main()
