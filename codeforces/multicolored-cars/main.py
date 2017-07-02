#!/usr/bin/env python3

from collections import defaultdict


MAX_N = 10 ** 6 + 1


def main():
    n, a = ints()
    colors = list(ints())

    # Count of each color
    counts = [0] * MAX_N

    # Map from count -> {Set of colors with this count...}
    index = defaultdict(set)
    index[0] = set(colors)

    for c in colors:
        k = counts[c]

        # Check if color c is...
        #   (1) previously eliminated
        #   (2) loses in this iteration which is the first encounter
        if k == -1 or k < counts[a]:
            continue

        # Update the count of color c
        counts[c] = k + 1
        index[k].remove(c)
        index[k + 1].add(c)

        if c == a:
            for x in index[k]:
                counts[x] = -1
            del index[k]
        else:
            assert counts[c] >= counts[a]

    sols = [c for c in range(MAX_N) if counts[c] > 0 and c != a]

    if len(sols) > 0:
        check(colors, a, sols[0])
        print(sols[0])
    else:
        print(-1)


def check(colors, a, b):
    """Checks that Bob wins with color b if Alice chooses color a."""
    x, y = 0, 0

    for c in colors:
        if c == a:
            x += 1
        elif c == b:
            y += 1
        assert x <= y, '%d is not a valid solution!' % b


def ints():
    """Returns a generator of integers from the next input line."""
    return (int(i) for i in input().split())

if __name__ == '__main__':
    main()
