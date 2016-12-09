#!/usr/bin/env python

from collections import deque


class Node(object):
    """Represents a multi-level linked list node."""

    def __init__(self, value):
        self.value = value
        self.next = None
        self.child = None

    def get(self, i):
        """Returns the ith node of the list."""
        node = self
        while i > 0 and node is not None:
            node = node.next
            i -= 1
        return node

    def __eq__(self, other):
        """Checks if two lists are identical. Does not check for cycles."""
        # Check these nodes
        if not isinstance(other, Node) or self.value != other.value:
            return False

        # Check next
        if self.next is not None and self.next != other.next:
            return False
        elif self.next is None and other.next is not None:
            return False

        # Check child
        if self.child is not None and self.child != other.child:
            return False
        elif self.child is None and other.child is not None:
            return False

        return True

    def __ne__(self, other):
        return not self == other

    @staticmethod
    def build(iterable):
        """Creates a single level linked list from an iterable."""
        head = Node(None)
        tail = head
        for x in iterable:
            tail.next = Node(x)
            tail = tail.next
        return head.next


def flatten(node):
    """Flattens a multi-level linked list.

    Args:
        node (Node): The head of the multi-level list we want to flatten

    Returns:
        Node: The head of the flattened list
    """
    if node is None:
        return None

    head = Node(None)
    tail = head
    queue = deque([node])

    while len(queue) > 0:
        node = queue.popleft()
        tail.next = node
        while node is not None:
            tail = node
            if node.child is not None:
                queue.append(node.child)
                node.child = None
            node = node.next

    return head.next


def main():
    # Create the levels
    one = Node.build([10, 5, 12, 7, 11])
    two = [Node.build([4, 20, 13]), Node.build([17, 6])]
    three = [Node.build([2]), Node.build([16]), Node.build([9, 8])]
    four = [Node.build([3]), Node.build([19, 15])]

    # Link the levels together
    one.child = two[0]
    one.get(3).child = two[1]

    two[0].get(1).child = three[0]
    two[0].get(2).child = three[1]
    two[1].child = three[2]

    three[1].child = four[0]
    three[2].child = four[1]

    # Create the expectation and ensure flatten works correctly
    expect = Node.build([10, 5, 12, 7, 11, 4, 20, 13,
                         17, 6, 2, 16, 9, 8, 3, 19, 15])
    assert flatten(one) == expect

if __name__ == '__main__':
    main()
