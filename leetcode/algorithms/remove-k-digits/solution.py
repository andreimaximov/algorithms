#!/usr/bin/env python


class Solution(object):
    def _min(self, number, i, length):
        """
        Returns the index of the smallest digit in the first length characters
        starting at i.
        """
        n = len(number)
        assert i >= 0
        assert i < n
        index = i
        for j in range(i + 1, min(n, i + length)):
            if number[j] < number[index]:
                index = j
        return index

    def _removeKdigits(self, number, i, k):
        """
        Returns the largest possible number by removing k digits from
        number[i:].
        """
        n = len(number)
        assert i >= 0
        assert i < n

        if k == 0:
            return number[i:]
        elif k >= n - i:
            # Delete all remaining digits.
            return ''

        # Since at most K digits can re removed from the start of the number,
        # the first digit in the result must be in the first K + 1 digits. Find
        # the smallest digit in the first K + 1 digits to keep as the first
        # digit in the result.
        j = self._min(number, i, k + 1)

        # Count how many number between i (inclusive) and j (exclusive) we are
        # deleting.
        deleting = j - i

        # Continue looking if we have not reached the end of the number yet.
        if j < n - 1:
            return number[j] + self._removeKdigits(number, j + 1, k - deleting)
        return number[j]

    def removeKdigits(self, number, k):
        n = len(number)
        if n == 0 or k == n:
            # Number is empty or can be made empty by removing all digits.
            return '0'
        elif k == 0:
            return number
        return str(int(self._removeKdigits(number, 0, k)))


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/contest/5/problems/remove-k-digits/')

if __name__ == '__main__':
    main()
