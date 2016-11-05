#!/usr/bin/env python


class Solution(object):
    def canCompleteCircuit(self, gas, cost):
        """
        Given the amount of gas at N gas stations and the how much gas it takes
        to travel from the ith to (i + 1) and N -> 1st gas station, is there a
        starting point which allows completing a full loop?

        The idea is to begin by checking if we can complete a full loop
        starting at the first gas station. Best case we can and the check takes
        O(N) time. But what if we have to cut our loop short due to not enough
        gas?

        Say we began our loop check at index i and were only able to get to
        index j. This means there was less gas available at station j than the
        amount needed to get from j to j + 1. The only way to cross from
        j to j + 1 is if we had more gas left when arriving at station j.
        However this is not possible to accomplish by starting from any station
        k where i <= k <= j. Thus no such station k is a viable starting point
        so instead we begin our next check at j + 1.

        We continue this process until we have either eliminated all stations
        or progressed through N stations without running out of gas - in which
        case we found a full loop!

        With this algorithm we go through each gas station no more than twice
        so the algorithm is O(N).
        """
        n = len(gas)
        assert n == len(cost)

        # Base case
        if n == 1:
            return -1 if gas[0] < cost[0] else 0

        start = 0

        # In each iteration consider the next start as a candidate for a
        # starting position that can complete a full loop.
        while start < n:
            # Must have at least enough gas to reach the second station.
            if gas[start] < cost[start]:
                start += 1
                continue

            # Continue to next station as long as there is enough gas.
            gasTank = 0
            i = 0
            while i < n:
                j = (start + i) % n
                gasTank += gas[j] - cost[j]
                if gasTank < 0:
                    # Not enough gas! We cannot start at any index
                    # [start, start + i] so skip to start + i + 1.
                    start = start + i + 1
                    break
                else:
                    i += 1
                    if i == n:
                        # Complete loop!
                        return start
        return -1


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/gas-station/')

if __name__ == '__main__':
    main()
