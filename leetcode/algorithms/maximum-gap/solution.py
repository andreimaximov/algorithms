#!/usr/bin/env python


POS_INF = float('inf')
NEG_INF = float('-inf')


class Solution(object):
    def maximumGap(self, nums):
        """
        Uses the Pigeonhole Principle to find the maximum gap between two
        adjacent integers in the sorted form of nums.

        Say N = len(nums), Xmax = max(nums), Xmin = min(nums). We create
        N intervals of k = (Xmax - Xmin) / N length to which we assign each n
        in nums. For example, the ith interval contains numbers in
        [Xmin + i * k, Xmin + (i + 1) * k]. The last interval is an exception
        which is actually [Xmin + i * k, Xmax] if N if the range of numbers is
        not evenly divisible by N.

        Consider the trivial case where there is exactly one n in each
        interval. We can iterate through the intervals in order and find the
        max gap where gap(i) = min(interval[i]) - max(interval[i - 1]).

        Imagine the numbers are not so evenly distributed and that there is
        more than 1 number in some inteval. This implies there are 0 numbers
        in some other interval! Note that the empty interval CANNOT be the last
        or first interval due to the first/last n being at the start/end of the
        first/last interval.

        This mean there is a gap >= k that crosses an empty interval which
        means we can ignore gaps between numbers in the same interval since
        these gaps < k!

        We can use this notion to make a small adjustment to our gap
        maximization formula. Call max*(interval[i]) the maximum number in the
        last non-empty interval. Thus, for each non-empty interval we say just
        maximize gap*(i) = min(interval[i]) - max*(interval[i - 1]).

        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n < 2:
            return 0

        lo = min(nums)
        hi = max(nums)

        # Handle trivial case where all numbers are the same.
        if lo == hi:
            return 0

        # The length of each interval. Floating point because we might have
        # more nums than the range of nums.
        length = (hi - lo) / float(n)

        # Count of numbers in each interval.
        intervals = [0 for _ in range(0, n)]

        # The minimum and maximum number in each interval.
        mins = [POS_INF for _ in range(0, n)]
        maxes = [NEG_INF for _ in range(0, n)]

        for n in nums:
            # Determine the interval this n belongs to.
            index = int((n - lo) / length)

            # The last interval might be a 1 longer. Check if we are out of
            # bounds when calculating index using length of first N - 1
            # intervals.
            if index == len(intervals):
                index -= 1

            # Update metrics for interval.
            intervals[index] += 1
            mins[index] = min(mins[index], n)
            maxes[index] = max(maxes[index], n)

        # The maximum number in the last non-empty interval. Remember that the
        # the first and last intervals are guaranteed to be non-empty.
        prevMax = maxes[0]
        maxGap = 0

        for index in range(1, len(intervals)):
            # Skip empty intervals.
            if intervals[index] == 0:
                continue
            maxGap = max(maxGap, mins[index] - prevMax)
            prevMax = maxes[index]

        return maxGap


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/maximum-gap/')

if __name__ == '__main__':
    main()
