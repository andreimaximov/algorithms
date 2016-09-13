#!/usr/bin/env python


class Solution(object):
    def maxProfit(self, prices):
        """
        Finds the maximum profit that can be achieved with at most two
        non-overlapping transactions. The problem can be split into an FSM with
        4 states.

        S0 = Began first transaction (Bought)
        S1 = Ended first transaction (Sold)
        S2 = Began second transaction (Bought)
        S3 = Ended second transaction (Sold)
        """
        # No way to make a profit without at least two days of history.
        if len(prices) < 2:
            return 0

        # Init S0 and S2 with the negative of the highest price. This is the
        # lowest possible drawdown with an optimal strategy.
        topPrice = max(prices)
        state = [- topPrice, 0, - topPrice, 0]

        for p in prices:
            nextState = list(state)

            # Either stay at this current state or buy at a lower price if
            # possible.
            nextState[0] = max(state[0], - p)

            # Stay at the current state or sell the stock we bought in S0 at a
            # higher price.
            nextState[1] = max(state[1], state[0] + p)

            # If we have a positive balance after completing the first
            # transaction, it makes sense to begin the second. There's no
            # reason to begin the second transaction if the first transaction
            # is in a losing position because we might be able to recoupe
            # losses by selling at a future price with may be higher.
            if state[1] > 0:
                nextState[2] = max(state[2], state[1] - p)

            # Stay at the current state for the second transaction or sell at a
            # higher price.
            nextState[3] = max(state[3], state[2] + p)

            state = nextState

        return max(state[1], state[3])


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/')

if __name__ == '__main__':
    main()
