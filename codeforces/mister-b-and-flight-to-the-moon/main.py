#!/usr/bin/env python3

from collections import defaultdict

DEBUG = False


def main():
    if DEBUG:
        test()

    n = int(input())

    paths = cycles(n)

    print(len(paths))
    for p in paths:
        print('%d %s' % (len(p), ' '.join([str(v) for v in p])))


def cycles(n):
    """Builds a set of cycles for a fully connected graph with n vertices."""
    if n % 2 == 0:
        return even(n)
    else:
        return odd(n)


def even(n):
    """Builds a set of cycles that a graph with even vertices."""
    assert n % 2 == 0

    # Base case for complete graph such that V = {1, 2, 3, 4}.
    cycles = [[1, 2, 3], [2, 3, 4], [3, 4, 1], [4, 1, 2]]

    for i in range(6, n + 1, 2):
        a, b = i, i - 1

        # Use edges (a, 1), (a, 0), (b, 1), (b, 0), (a, b) exactly twice each.
        cycles += [[a, 1, b], [a, 2, b], [a, 1, b, 2]]

        # Similar to odd(...) as we are left with 2n - 2 edges to use
        # connected to i - 4 of the vertices V' = {3 ... i - 2}. Notice that
        # |V'| is even so we can apply the same strategy as in odd(...).
        for k in range(3, i - 1, 2):
            c, d = k, k + 1
            cycles += [[a, c, b, d]] * 2

    return cycles


def odd(n):
    """Builds a set of cycles that a graph with odd vertices."""
    assert n % 2 == 1

    # Base case for complete graph such that V = {1, 2, 3}.
    cycles = [[1, 2, 3]] * 2

    for i in range(5, n + 1, 2):
        a, b = i, i - 1
        # Say the new vertices are {a, b}. Since the graph is fully connected
        # adding these 2 vertices results in 2n + 1 more edges. We use a length
        # 3 cycle a -> b -> 1 > a twice to use up 3 of these edges.
        cycles += [[a, b, 1]] * 2

        # At this point we are left with 2n + 1 - 3 = 2n - 2 edges to use
        # connected to i - 3 of the vertices V' = {2 ... i - 2}. Notice that
        # |V'| is even. To use these edges and cover vertices V' we take pairs
        # c, d in V' and create two of each path a -> c -> b -> d -> a.
        for k in range(2, i - 1, 2):
            c, d = k, k + 1
            cycles += [[a, c, b, d]] * 2

    return cycles


def test():
    """Checks the cycles(...) solver for a bunch of inputs."""
    print('Testing...')

    for n in range(3, 300, 21):
        check(n, cycles(n))

    print('Tests pass!')


def check(n, paths):
    """Checks the solution for errors."""
    # Check that all vertices are covered.
    vertices = set(sum(paths, list()))
    assert vertices == set(range(1, n + 1))

    # Check that each edge is used exactly twice.
    counts = defaultdict(int)

    for p in paths:
        assert len(p) == 3 or len(p) == 4
        assert len(set(p)) == len(p)

        for i in range(len(p)):
            key = tuple(sorted([p[i - 1], p[i]]))
            counts[key] += 1

    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            assert counts[(i, j)] == 2

if __name__ == '__main__':
    main()
