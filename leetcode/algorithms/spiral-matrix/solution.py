#!/usr/bin/env python


class Solution(object):
    def spiralOrder(self, matrix):
        """
        Returns the clockwise spiral order traversal of the matrix starting at
        (0, 0). Modifies the matrix to contain all None values.

        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        if len(matrix) == 0 or len(matrix[0]) == 0:
            return []

        # Size of the matrix.
        n = len(matrix)
        m = len(matrix[0])

        # Current row and column that we are on.
        r = 0
        c = 0

        # The delta values to get the next row and column.
        dr = 0
        dc = 1

        # The resulting spiral order and next insertion index.
        spiral = [0] * (n * m)
        i = 0

        for i in range(0, n * m):
            spiral[i] = matrix[r][c]
            matrix[r][c] = None  # Mark this cell as visited
            i += 1

            # Check if the current delta will result in revisting a cell.
            nextr = (r + dr) % n
            nextc = (c + dc) % m
            if matrix[nextr][nextc] is None:
                dr, dc = dc, -dr  # Turn right.

            # Go to next cell.
            r += dr
            c += dc

        return spiral


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/spiral-matrix/')

if __name__ == '__main__':
    main()
