#!/usr/bin/env python


from heapq import *


class Solution(object):
    def kthSmallest(self, matrix, k):
        """
        Returns the kth smallest element in a matrix with rows and columns
        sorted in ascending order. This is an O(N + KlogN) algorithm.
        """
        n = len(matrix)
        assert k >= 1
        assert k <= n**2

        # Min heap of tuples representing the (value, row, col) of potential
        # candidate cells.
        candidates = [(matrix[r][0], r, 0) for r in xrange(0, n)]
        heapify(candidates)

        # The inorder position of the next candidate we can pop from the heap.
        position = 1

        # In each iteration of the loop traverse to the right across the lowest
        # value cell. The next cell is always GTE to the current cell.
        while position < k:
            (value, r, c) = heappop(candidates)
            position += 1

            # If there is a cell to the right of the one we just popped, add it
            # to the heap.
            if c < n - 1:
                heappush(candidates, (matrix[r][c + 1], r, c + 1))

        return heappop(candidates)[0]


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/')  # nopep8

if __name__ == '__main__':
    main()
