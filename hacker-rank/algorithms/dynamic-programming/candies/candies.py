#!/usr/bin/env python

import sys


def candies(children):
    length = len(children)

    if (length <= 1):
        return length

    candies = [1] * length

    # Perform left to right rankings
    for i in range(1, length):
        if (children[i] > children[i - 1]):
            candies[i] = candies[i - 1] + 1

    # Tracks number of candies
    count = candies[length - 1]

    # Perform right to left rankings
    for i in range(length - 1, 0, -1):
        if (children[i - 1] > children[i]):
            candies[i - 1] = max(candies[i - 1], candies[i] + 1)
        count += candies[i - 1]

    return count


def main():
    n = int(sys.stdin.readline())
    children = [0] * n
    for i in range(0, n):
        children[i] = int(sys.stdin.readline())
    print(candies(children))


if __name__ == '__main__':
    main()
