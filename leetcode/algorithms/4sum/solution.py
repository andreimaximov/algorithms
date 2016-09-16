#!/usr/bin/env python


class Solution(object):
    def kSum(self, nums, start, target, k):
        """
        Finds all unique k-tuples of numbers in nums[start:] that sum up to the
        given target. nums is expected to be sorted from smallest to largest.
        This is a O(N^(K - 1)) algorithm where N = len(nums) because up to N
        sub-problems are calculated in each call a total of K - 1 levels. The
        algorithm terminates after K = 2 is calculated in O(N) time.

        See http://www.sigmainfy.com/blog/k-sum-problem-analysis-recursive-implementation-lower-bound.html # nopep8
        """
        assert k > 1
        if k == 2:
            return self.twoSum(nums, start, target)

        n = len(nums)
        tuples = []

        # Loop through and try to use each element as the first value in the
        # k-tuple adding up to the target.
        for i in range(start, n):
            # We need to carefully handle repeating values to avoid duplicate
            # tuples. This will ensure that for x repeating y values, we
            # consider {1, 2 ... x} y's only once each.
            if i > start and nums[i - 1] == nums[i]:
                continue
            include = self.kSum(nums, i + 1, target - nums[i], k - 1)
            for extend in include:
                extend.append(nums[i])
                tuples.append(extend)

        return tuples

    def twoSum(self, nums, start, target):
        """
        Finds all unique 2-tuples of numbers in nums[start:] that sum up to the
        given target. nums is expected to be sorted from smallest to largest.
        This is a O(N) algorithm where N = len(nums).
        """
        left = start
        right = len(nums) - 1
        solutions = []

        while left < right:
            # If we have already encountered the left side element we skip it
            # to avoid duplicate tuples.
            if left > start and nums[left - 1] == nums[left]:
                left += 1
                continue
            candidate = nums[left] + nums[right]
            if candidate == target:
                solutions.append([nums[left], nums[right]])
                left += 1
                right -= 1
            elif candidate < target:
                left += 1
            else:
                right -= 1

        return solutions

    def fourSum(self, nums, target):
        """
        Finds all unique 4-tuples of numbers that sum up to the given target.
        """
        nums = sorted(nums)
        return self.kSum(nums, 0, target, 4)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/flatten-binary-tree-to-linked-list/')

if __name__ == '__main__':
    main()
