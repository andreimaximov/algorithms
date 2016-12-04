#!/usr/bin/env python

from generators import SegmentTreeGenerator, ArrayGenerator, DictGenerator

SAMPLES = 250000

INIT_DATA = {'a': 1, 'b': 2, 'c': 3, 'd': 4}
UPDATE_DATA = {'a': 2, 'b': 1, 'c': 3, 'd': 10}

UPDATES = [('a', 2), ('b', 1), ('d', 10)]

GENERATORS = [
    SegmentTreeGenerator,
    ArrayGenerator,
    DictGenerator
]


def test(generator, data):
    # Collect data over samples.
    results = {value: 0 for value in data.keys()}
    for _ in range(0, SAMPLES):
        value = generator.random()
        results[value] += 1

    # Normalize result frequencies.
    for value in results:
        results[value] /= float(SAMPLES)

    # Check that the distribution is roughly proportional to the frequency. We
    # could use a T-test here to be more mathematicaly precise with our test.
    total = sum(data.values())
    expect = {value: data[value] / total for value in data.keys()}
    for value in expect:
        assert abs(results[value] - expect[value]) < 0.01


def main():
    for generator_class in GENERATORS:
        print('Testing %s...' % generator_class.__name__)

        # Test the generator with the initial distribution.
        generator = generator_class(INIT_DATA)
        test(generator, INIT_DATA)

        # Update weights and re-test the distribution of random values.
        for (value, weight) in UPDATES:
            generator.update(value, weight)
        test(generator, UPDATE_DATA)
    print('All tests pass!')


if __name__ == '__main__':
    main()
