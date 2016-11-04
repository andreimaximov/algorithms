#!/usr/bin/env python

from range_map import RangeMap


DATA = [
    [('a', 1), ('b', 2), ('c', 3)]
]

#
# Test cases for interval queries in the range map. Each value is a tuple
# (point, expect) where the test performs a query on the specified point and
# ensures the expected value is returned.
#
QUERIES = [
    [
        (-0.1, None),
        (0.5, 'a'),
        (1, 'b'),
        (2.1, 'b'),
        (2.999, 'b'),
        (3.5, 'c'),
        (6.1, None)]
]

#
# Test cases for updating value intervals in the range map. Each value is a
# tuple (value, interval, point, expect) where the test updates the interval
# for the specified value, and performs a point query ensuring the expected
# value is returned.
#
UPDATES = [
    [('a', 2, 1, 'a'), ('a', 0.5, 0.75, 'b'), ('b', 0, 1, 'c')]
]


def test(test_case):
    rm = RangeMap(DATA[test_case])

    print('Testing query...')
    for (point, expect) in QUERIES[test_case]:
        assert expect == rm.get(point)

    print('Testing updates...')
    for (value, interval, point, expect) in UPDATES[test_case]:
        rm.update(value, interval)
        assert expect == rm.get(point)

    print('Test case %d passes!' % (test_case + 1))


def main():
    for test_case in range(0, len(DATA)):
        test(test_case)
    print('All tests pass!')


if __name__ == '__main__':
    main()
