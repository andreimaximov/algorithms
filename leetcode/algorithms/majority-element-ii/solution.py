#!/usr/bin/env python

TEST_INPUTS = [
    ([0, 0, 0], 3),
    ([1, 1, 1, 2, 2], 2),
    ([1, 1, 1, 2, 2, 2, 3, 4], 3)
]

TEST_OUTPUTS = [
    [0],
    [1],
    [1, 2]
]


class Solution(object):
    def majorityElement(self, nums):
        """
        O(n) algorithm for finding all elements that occur more than n / 3
        times.

        :type nums: List[int]
        :rtype: List[int]
        """
        return self.kMajorityElement(nums, 3)

    def kMajorityElement(self, nums, k):
        """
        O(nk) algorithm for finding all elements in an unsorted array that
        occur more than n / k times. Generalized Boyer-Moore algorithm.

        Reference: http://www.geeksforgeeks.org/given-an-array-of-of-size-n-finds-all-the-elements-that-appear-more-than-nk-times/ # noqa

        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        assert k > 1

        # At most k - 1 elements can occur more than n / k times. Each entry
        # is a (number, count) pair.
        counts = [[None, 0] for i in range(0, k - 1)]

        for n in nums:
            done = False

            # Check if this number has an existing entry.
            for c in counts:
                if c[0] == n:
                    c[1] += 1
                    done = True
                    break

            # Existing entry updated.
            if done:
                continue

            # Insert new entry if there is space.
            for c in counts:
                if c[1] is 0:
                    c[0] = n
                    c[1] = 1
                    done = True
                    break

            # New entry inserted.
            if done:
                continue

            # Decrement all counts by 1.
            for c in counts:
                c[1] = max(0, c[1] - 1)

        # Reset candidate counts to 0.
        counts = [[c[0], 0] for c in counts]

        # Checks if candidates actually occur more than n / k times.
        for n in nums:
            for c in counts:
                if c[0] == n:
                    c[1] += 1

        return [c[0] for c in counts if c[1] > len(nums) / k]


def main():
    solution = Solution()
    for i in range(0, len(TEST_INPUTS)):
        print('Running test %d...' % (i + 1))
        arr = TEST_INPUTS[i][0]
        k = TEST_INPUTS[i][1]
        assert TEST_OUTPUTS[i] == solution.kMajorityElement(arr, k)

    print('Tests pass!')
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/majority-element-ii/')


if __name__ == "__main__":
    main()
