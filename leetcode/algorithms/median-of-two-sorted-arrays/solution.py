#!/usr/bin/env python


class Solution(object):
    def findMedianSortedArrays(self, a, b):
        """
        Returns the median of two sorted arrays a and b.
        """
        n = len(a) + len(b)
        if n % 2 == 0:
            # If the total length is even, take the average of the two medians.
            return (self._findKth(a, 0, b, 0, n // 2) +
                    self._findKth(a, 0, b, 0, n // 2 + 1)) / 2.0
        else:
            return self._findKth(a, 0, b, 0, n // 2 + 1)

    def _findKth(self, a, i, b, j, k):
        """
        Returns the kth element of two sorted sub-arrays a[i:] and b[j:]. The
        high level description of the algorithm is as follows.

        Call A = a[i:], B = b[j:], and n the kth element. In each iteration of
        the algorithm we wish to get k / 2 closer to the kth element. To do
        this we compare A[k / 2] and B[k / 2] where A = X + [A[k / 2]] + Y and
        B = Z + [B[k / 2]] + J.

        Note that |Z| = |X| = k / 2 - 1. This helps us consider 2 cases.

        1. A[k / 2] < B[k / 2] -> n is not in X and n != A[k / 2]. Why?

        We know for sure that all elements in X are part of the k - 2 smallest
        elements because all x in X <= all y in Y, x < all j in J,
        x <= A[k / 2] and x < B[k / 2]. This only leaves the relationship
        between each x and each z in Z uncertain.

        The same cannot be said about Z because some z in Z could be > some
        y in Y. Thus we can eliminate only X and A[k / 2] from our search which
        brings us k / 2 closer to our target.

        2. A[k / 2] >= B[k / 2] -> n is not in Y or {B[k / 2]} using similar
        logic.

        The main edge cases arises when len(A) < k / 2 or len(B) < k / 2. Say
        len(A) < k / 2. This means we can cut out the first k / 2 of B. Why?

        1. If all a in A >= first k / 2 b in B -> No b in first k / 2 of B = n.

        2. If all a in A < first k / 2 b in B -> There is no a in A that = n.

        Similar logic holds for A when len(B) < k.
        """
        assert k <= len(a) + len(b)

        if i >= len(a):
            # Out of bounds of a.
            return b[j + k - 1]
        elif j >= len(b):
            # Out of bounds of b.
            return a[i + k - 1]
        elif k == 1:
            # 1st element is the smaller of the first in a or b.
            return min(a[i], b[j])

        midAIndex = i + k // 2 - 1

        # Handle case where a[i:] is shorter than k // 2. We will keep this
        # array and cut the other one instead which is guaranteed to be at
        # least length k // 2
        midAValue = a[midAIndex] if midAIndex < len(a) else float('inf')

        midBIndex = j + k // 2 - 1

        # Same case as midAValue but for b.
        midBValue = b[midBIndex] if midBIndex < len(b) else float('inf')

        if midAValue < midBValue:
            return self._findKth(a, midAIndex + 1, b, j, k - k // 2)
        else:
            return self._findKth(a, i, b, midBIndex + 1, k - k // 2)


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/median-of-two-sorted-arrays/')

if __name__ == '__main__':
    main()
