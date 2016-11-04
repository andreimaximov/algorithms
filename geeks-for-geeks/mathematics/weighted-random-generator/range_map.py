#!/usr/bin/env python


class RangeMap(object):
    """
    Maps values to an interval and allows efficiently querying the value that
    corresponds to a particular point in the continuous range of intervals for
    all values.

    For example given the values and interval lengths [(a, 1), (b, 2), (c, 3)]
    creates a Segment Tree mapping each value to the following intervals.

    a -> [0, 1)
    b -> [1, 3)
    c -> [3, 6)

    Querying on point 4.5 will return the value c. If we update the length of
    interval b, all intervals after it will shift. For example if we update
    the length of inteval b to 4 we will get the following interval mapping.

    a -> [0, 1)
    b -> [1, 5)
    c -> [5, 8)

    Provides O(log(N)) query and update performance using a Segment Tree.
    """

    def __init__(self, data):
        """
        :type data: List[T, float] - Each item and the length of the interval
                                     it belongs to.
        """
        assert len(data) > 0
        self._values = dict()  # Maps each value to the leaf node it is in.
        leafs = RangeMap._leafs(data)
        self._root = self._build(leafs, 0, len(leafs) - 1)

    def _build(self, leafs, lo, hi):
        """
        Builds the segment tree.
        """
        assert lo >= 0
        assert hi < len(leafs)
        assert lo <= hi

        if lo == hi:
            self._values[leafs[lo].value] = leafs[lo]
            return leafs[lo]

        mid = lo + (hi - lo) // 2
        left = self._build(leafs, lo, mid)
        right = self._build(leafs, mid + 1, hi)

        root = RangeMap.Node(None, left.begin, left.end, left.end + right.end)
        root.left = left
        left.parent = root
        root.right = right
        right.parent = root
        return root

    def get(self, point):
        """
        Finds the value corresponding to the interval the point lies in. Takes
        O(log(N)) time.

        :type point: float
        :rtype: T - The element mapping to the interval the point is in.
        """
        if point < 0 or point >= self._root.end:
            return None
        node = self._root
        while not node.isLeaf():
            if point < node.split:
                node = node.left
            else:
                point -= node.split
                node = node.right
        return node.value

    def update(self, value, length):
        """
        Updates the length of the interval the value belongs to. Shifts all
        intervals after the value. Takes O(log(N)) time.
        """
        assert value in self._values
        leaf = self._values[value]
        leaf.end = length

        node = leaf.parent
        while node is not None:
            node.begin = node.left.begin
            node.split = node.left.end
            node.end = node.left.end + node.right.end
            node = node.parent

    def range(self):
        """
        Returns the length of the top level interval over all values.
        """
        return self._root.end

    @staticmethod
    def _leafs(data):
        """
        :type data: List[(T, float)]
        :rtype: List[ValueNode]
        """
        leafs = []
        for (value, length) in data:
            if length < 0:
                raise ValueError('interval must be >= 0')
            node = RangeMap.Node(value, 0, 0, length)
            leafs.append(node)
        return leafs

    class Node(object):
        """
        Represents a node in the Segment Tree.
        """
        def __init__(self, value, begin, split, end):
            self.value = value
            self.begin = begin
            self.split = split
            self.end = end
            self.left = None
            self.right = None
            self.parent = None

        def isLeaf(self):
            return self.value is not None

        def __str__(self):
            return str({
                'value': self.value,
                'range': (self.begin, self.split, self.end)})
