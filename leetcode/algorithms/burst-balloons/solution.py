#!/usr/bin/env python


class Solution(object):
    def maxCoins(self, balloons):
        """Returns the max coins with an optimal popping strategy.

        Args:
            balloons (List[int]): Balloon coin values.

        Returns:
            The max coins as an int.
        """
        n = len(balloons)
        if n == 0:
            return 0
        elif n == 1:
            return balloons[0]

        # Each dp[i][j] stores the max coins one can get by popping
        # balloons[i...j] BEFORE balloon i and j.
        dp = [[-1 for _ in xrange(n)] for _ in xrange(n)]

        return self.maxCoinsHelper(balloons, 0, n - 1, dp, 1, 1)

    def maxCoinsHelper(self, balloons, lo, hi, dp, left, right):
        """Returns the max coins popping balloons[lo...hi] optimally.

        The overall strategy is that each time we consider each balloon x as
        the LAST balloon we will pop in balloons[lo...hi]. This way we can
        be sure that the left/right adjacent balloon for the sub-problems will
        be x.
        """
        if hi < 0 or lo >= len(dp):
            return 0
        elif dp[lo][hi] != -1:
            return dp[lo][hi]
        elif lo == hi:
            # This works because left = balloons[lo - 1] and right =
            # balloons[hi + 1] each time dp[i][i] is reused. See definition of
            # dp array in maxCoins(...) function.
            dp[lo][hi] = left * balloons[lo] * right
            return dp[lo][hi]

        coins = 0

        for i in xrange(lo, hi + 1):
            x = balloons[i]  # Last balloon we will pop in balloons[lo...hi].
            leftCoins = self.maxCoinsHelper(balloons, lo, i - 1, dp, left, x)
            rightCoins = self.maxCoinsHelper(balloons, i + 1, hi, dp, x, right)
            coins = max(coins, leftCoins + left * x * right + rightCoins)

        dp[lo][hi] = coins
        return coins


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/burst-balloons/')

if __name__ == '__main__':
    main()
