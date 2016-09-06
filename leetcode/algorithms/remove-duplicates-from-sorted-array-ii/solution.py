#!/usr/bin/env python


class Solution(object):
    def lastIndexOf(self, array, target, start, end):
        """
        Finds the last index of target in range [start...end] of array. Returns
        -1 if the target does not exist. The array is expected to be sorted in
        ascending order and array[start] must be the target for the search to
        continue.
        """
        assert start <= end

        if array[start] != target:
            return -1
        elif start == end:
            return start

        i = start
        step = 1

        # Use modified binary search to find last occurence of target by
        # doubling step distance each iteration.
        while True:
            if i == end:
                return i
            j = i + step
            step *= 2
            if j > end or array[j] != target:
                # Reset step distance and continue from last i where
                # array[i] == target.
                candidate = self.lastIndexOf(array, target, i + 1, end)
                # Ignores candidate if candidate == -1
                return max(i, candidate)
            i = j

    def removeDuplicates(self, nums, k=2):
        """
        Removes duplicates from sorted array nums so that there are at most k
        duplicates.

        Algorithm runs in O(N) time worst case and O(logN) time in the best
        case.
        """
        n = len(nums)

        # No way to have more than k duplicates with k or less elements.
        if n <= k:
            return n

        # The index where elements will be inserted into.
        insert = 0

        # The index from which we will be reading/processing elements.
        get = 0

        while get < n:
            # Get target and count the number of duplicates.
            target = nums[get]
            last = self.lastIndexOf(nums, target, get, n - 1)
            occurences = last - get + 1

            # Copy the first min(k, occurences) of target into the array.
            for i in range(get, get + min(k, occurences)):
                nums[insert] = nums[i]
                insert += 1

            # Continue searching for next target after the index of the last
            # target.
            get = last + 1

        return insert


def test(input, expect):
    sol = Solution()
    length = sol.removeDuplicates(input)
    actual = input[0:len(expect)]
    try:
        assert len(expect) == length
        assert expect == actual
    except AssertionError:
        print('Expected %s but got %s.' % (expect, actual))
        raise


def main():
    test([], [])
    test([1], [1])
    test([1, 2, 3], [1, 2, 3])
    test([1, 1, 1, 2, 2, 3], [1, 1, 2, 2, 3])
    print('Tests pass!')
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/'
          'remove-duplicates-from-sorted-array-ii/')


if __name__ == "__main__":
    main()
