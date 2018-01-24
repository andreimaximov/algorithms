#!/usr/bin/env python

import sys


def read(fn):
    return fn(sys.stdin.readline())


def ceil(array, value):
    """
    Returns the smallest index i such that array[i - 1] < value.
    """
    l = 0
    r = len(array) - 1
    i = r + 1

    while l <= r:
        m = l + int((r - l) / 2)
        if array[m] >= value:
            # This mid index is a candidate for the index we are searching for
            # so save it, and continue searching for a smaller candidate on the
            # left side.
            i = m
            r = m - 1
        else:
            # This mid index is not a candidate so continue searching the right
            # side.
            l = m + 1

    return i


def lis(array):
    """
    Returns the length of the longest increasing sub-sequence in O(NlogN) time.

    See http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/. # nopep8
    """
    n = len(array)
    if n < 2:
        return n

    # Stores the last value for each candidate increasing list. We maintain
    # that last value in shorter lists is less than the last value in longer
    # lists.
    tails = [array[0]]

    for i in range(1, n):
        a = array[i]
        if a <= tails[0]:
            # Begin the shortest LIS at this new smallest element for the most
            # possible future LIS candidates.
            tails[0] = a
        elif tails[-1] < a:
            # Create a new longest LIS ending with this new largest element.
            tails.append(a)
        else:
            # Find a LIS where we can replace the last element with a.
            j = ceil(tails, a)
            tails[j] = a

    return len(tails)


def lis_dp(array):
    """
    Returns the length of the longest increasing sub-sequence in O(N^2) time.
    This is not fast enough to pass with the HackerRank time constraints.
    """
    n = len(array)
    if n == 0:
        return 0

    dp = [1] * n

    # Let F(i) be the LIS ending with array[i]. F[i] = max({1 + F[j]}) for all
    # j < i and array[j] < array[i]. If no such j exists, then F[i] = 1.
    for i in range(1, n):
        for j in range(0, i):
            if array[j] < array[i]:
                dp[i] = max(dp[i], 1 + dp[j])

    return max(dp)


def main():
    N = read(int)
    array = [0] * N
    for i in range(0, N):
        array[i] = read(int)
    print(lis(array))

if __name__ == '__main__':
    main()
