#!/usr/bin/env python

import sys


def read_ints():
    line = sys.stdin.readline().strip()
    return [int(x) for x in line.split(" ")]


def change(cents, denom, coins, cache):
    # The value in cents of the current coint we are using for change.
    coin = coins[denom]

    # If this is the last coin check if it can divide the remaining cents.
    if (denom == (len(coins) - 1)):
        return int((cents % coin) == 0)

    # Check if we have calculated this cents/coin combo before.
    if (denom in cache and cents in cache[denom]):
        return cache[denom][cents]

    # Calculate the number of ways to give change using increasing quantities
    # of this coin.
    ways = 0
    nextDenom = denom + 1
    currentCents = cents
    while (currentCents >= 0):
        ways += change(currentCents, nextDenom, coins, cache)
        currentCents -= coin

    # Store result to cache.
    if (denom not in cache):
        cache[denom] = {}
    cache[denom][cents] = ways

    return ways


def main():
    (N, M) = read_ints()
    coins = read_ints()
    print(change(N, 0, coins, {}))


if __name__ == '__main__':
    main()
