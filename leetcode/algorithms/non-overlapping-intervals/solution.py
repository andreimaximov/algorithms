#!/usr/bin/env python


class Solution(object):
    def eraseOverlapIntervals(self, intervals):
        """
        Proof of Correctness:
        http://lonati.di.unimi.it/algo/0910/lab/kowalski6.pdf

        :type intervals: List[Interval]
        :rtype: int
        """
        n = len(intervals)
        if n < 2:
            return 0

        # Sort intervals by (1) end point in increasing order and (2) start
        # point in decreasing order.
        intervals = list(sorted(intervals,
                         key=lambda itr: (itr.end, -itr.start)))

        erase = 0
        end = intervals[0].end
        for i in range(1, n):
            itr = intervals[i]
            if itr.start >= end:
                end = itr.end
            else:
                erase += 1

        return erase


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/non-overlapping-intervals/')

if __name__ == '__main__':
    main()
