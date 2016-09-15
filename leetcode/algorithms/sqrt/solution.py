#!/usr/bin/env python


class Solution(object):
    def mySqrt(self, x):
        assert x >= 0
        if x < 2:
            # Take care of base cases 0 and 1.
            return x

        lo = 1
        hi = x - 1
        root = lo

        # Use binary search to find largest root such that root^2 <= x
        while lo <= hi:
            mid = lo + int((hi - lo) / 2)
            square = mid**2
            if square == x:
                # Found exact match.
                return mid
            elif square <= x:
                # Found a square root candidate. Continue for searchig a larger
                # candidate.
                root = mid
                lo = mid + 1
            else:
                # Square is too large. Continue looking for smaller candidates.
                hi = mid - 1

        return root


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/sqrtx/')

if __name__ == '__main__':
    main()
