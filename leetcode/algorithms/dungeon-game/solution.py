#!/usr/bin/env python


class Solution(object):
    def _minHp(self, dungeon, m, n, y, x, dp):
        """
        Calculates the minimum HP needed to get from (x,y) in the dungeon to
        the bottom-right without reaching 0 HP by moving only right or down
        in the grid.

        :type dungeon: List[List[int]]
        :type m: int The number of rows in the dungeon grid
        :type n: int The number of columns in the dungeon grid
        :type y: int
        :type x: int
        :type dp: List[List[int]] The cache for each (x, y) starting position.
        """
        assert m > 0
        assert n > 0
        assert y >= 0
        assert y < m
        assert x >= 0
        assert x < n

        # Check if we have calculated this problem before.
        if dp[y][x] != -1:
            return dp[y][x]

        here = -dungeon[y][x]
        if y == m - 1 and x == n - 1:
            # Case I - (Base) Starting at bottom-right corner.
            dp[y][x] = max(1, here + 1)
        elif y == m - 1:
            # Case II - Along last bottom row.
            right = self._minHp(dungeon, m, n, y, x + 1, dp)
            dp[y][x] = max(1, here + right)
        elif x == n - 1:
            # Case III - Along last right column.
            down = self._minHp(dungeon, m, n, y + 1, x, dp)
            dp[y][x] = max(1, here + down)
        else:
            # Case IV - (General) Can go right or down mid dungeon.
            right = self._minHp(dungeon, m, n, y, x + 1, dp)
            down = self._minHp(dungeon, m, n, y + 1, x, dp)
            # Choose the shortest path of going right or down.
            dp[y][x] = max(1, here + min(right, down))

        return dp[y][x]

    def calculateMinimumHP(self, dungeon):
        """
        Calculates the minimum HP needed to get from the top-left corner of the
        dungeon to the bottom-right without reaching 0 HP.

        :type dungeon: List[List[int]]
        :rtype: int
        """
        m = len(dungeon)
        assert m > 0
        n = len(dungeon[0])
        dp = [([-1] * n) for _ in xrange(0, m)]
        return self._minHp(dungeon, m, n, 0, 0, dp)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/dungeon-game/')

if __name__ == '__main__':
    main()
