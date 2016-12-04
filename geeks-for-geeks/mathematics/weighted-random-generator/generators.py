#!/usr/bin/env python

import random
import functools
from range_map import RangeMap


class SegmentTreeGenerator(object):
    """
    Returns random elements with a probability proportional to the frequency
    distribution of each element in the population in O(log(N)) time. Uses up
    to 2N space but Supports O(log(N)) weight updates.
    """

    def __init__(self, population):
        """
        :type population: Dict[T, double]
        """
        data = list(map(lambda value: (value, float(population[value])),
                        population.keys()))
        self._range_map = RangeMap(data)

    def random(self):
        """
        Returns an element from the original population with probability
        proportional to its relative frequency. O(log(N)) time.

        :rtype: T
        """
        i = random.random() * self._range_map.range()
        return self._range_map.get(i)

    def update(self, value, weight):
        """
        Updates the weight of the value in the population. O(log(N)) time.
        """
        self._range_map.update(value, weight)


class ArrayGenerator(object):
    """
    Returns random elements with a probability proportional to the frequency
    distribution of each element in the population in O(log(N)) time. Uses
    N space but weight updates are proportional to O(N) time.
    """

    def __init__(self, population):
        """
        :type population: Dict[T, double]
        """
        assert len(population) > 0
        self._data = list()
        self._index = dict()
        self._total = float(sum(population.values()))
        offset = 0
        for value in population:
            weight = population[value]
            if weight < 0:
                raise ValueError('weights must be >= 0')
            self._index[value] = len(self._data)
            self._data.append(ArrayGenerator.Entry(value, offset, weight))
            offset += weight

    def random(self):
        """
        Returns an element from the original population with probability
        proportional to its relative frequency. O(log(N)) time.

        :rtype: T
        """
        i = random.random() * self._total
        j = 0
        while j < len(self._data) - 1 and self._data[j + 1].offset <= i:
            j += 1
        return self._data[j].value

    def update(self, value, weight):
        """
        Updates the weight of the value in the population. O(N) time.
        """
        assert value in self._index
        assert weight >= 0

        # Compute the change in offset for following values.
        i = self._index[value]
        delta = weight - self._data[i].weight
        self._data[i].weight = weight

        # Update offset for following values.
        i += 1
        while i < len(self._data):
            self._data[i].offset += delta
            i += 1

        # Update total.
        self._total += delta

    class Entry(object):
        def __init__(self, value, offset, weight):
            self.value = value
            self.offset = offset
            self.weight = weight


class DictGenerator(object):
    """
    Returns random elements with a probability proportional to the frequency
    distribution of each element in the population in O(N) time but weight
    updates take O(1) time.
    """
    def __init__(self, population):
        """
        :type population: Dict[T, double]
        """
        self._population = dict(population)
        self._total = functools.reduce(lambda s, key: population[key] + s,
                                       population,
                                       0)

    def random(self):
        """
        Returns an element from the original population with probability
        proportional to its relative frequency. O(N) time.

        :rtype: T
        """
        i = random.random() * self._total
        prefix = 0

        for key in self._population:
            prefix += self._population[key]
            if prefix >= i:
                return key

        raise RuntimeError('This should never happen...')

    def update(self, value, weight):
        """
        Updates the weight of the value in the population. O(1) time.
        """
        assert value in self._population
        assert weight >= 0

        current = self._population[value]
        self._total += (weight - current)
        self._population[value] = weight
