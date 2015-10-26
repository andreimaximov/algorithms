#!/usr/bin/env python

import sys
from queue import PriorityQueue


WRONG_MESSAGE = "Wrong!"


class HeapMultiSet(object):
    def __init__(self, prioritizer):
        self.prioritizer = prioritizer
        self.heap = PriorityQueue()
        self.counts = {}
        self.length = 0

    def offer(self, value):
        # Add the value to the heap if it does not exist yet.
        if (value not in self.counts or self.counts[value] <= 0):
            # Calculate a priority for the value
            priority = self.prioritizer(value)
            self.heap.put((priority, value))
            # Track the count of the value
            self.counts[value] = 0

        self.counts[value] += 1

        # Update the size of the heap
        self.length += 1

    def peek(self):
        if (self.heap.empty()):
            return None
        (priority, value) = self.heap.queue[0]
        return value

    def remove(self, value):
        if (not self.contains(value)):
            return False
        if (self.counts[value] > 0):
            self.length -= 1
            self.counts[value] = self.counts[value] - 1
            self.fix_top()
        return True

    def pop(self):
        if (self.heap.empty()):
            return None
        value = self.peek()
        if (self.counts[value] > 0):
            self.counts[value] -= 1
            self.length -= 1
            self.fix_top()
        return value

    def fix_top(self):
        while (not self.heap.empty()):
            (priority, value) = self.heap.queue[0]
            if (self.counts[value] > 0):
                break
            self.heap.get()

    def contains(self, value):
        return value in self.counts and self.counts[value] > 0

    def __len__(self):
        return self.length


class Median(object):
    def __init__(self):
        self.left = HeapMultiSet(lambda v: -v)
        self.right = HeapMultiSet(lambda v: v)

    def add(self, num):
        if (len(self.left) > len(self.right)):
            if (num >= self.left.peek()):
                self.right.offer(num)
            else:
                self.right.offer(self.left.pop())
                self.left.offer(num)
        else:
            if (len(self.right) > 0 and num >= self.right.peek()):
                self.left.offer(self.right.pop())
                self.right.offer(num)
            else:
                self.left.offer(num)

    def remove(self, num):
        if (len(self.left) == 0):
            return False

        container = self.left if (num <= self.left.peek()) else self.right
        if (not container.remove(num)):
            return False

        skew = len(self.left) - len(self.right)

        if (skew > 1):
            self.right.offer(self.left.pop())
        elif (skew < 0):
            self.left.offer(self.right.pop())

        return True

    def median(self):
        if (len(self.left) == 0):
            return None

        if (len(self.left) == len(self.right)):
            return (self.left.peek() + self.right.peek()) / 2
        else:
            return self.left.peek()


def format_result(result):
    if (result is None):
        return WRONG_MESSAGE
    elif (int(result) == result):
        return int(result)
    return result


def main():
    N = int(sys.stdin.readline())
    median = Median()
    while (N > 0):
        N = N - 1

        (op, num) = sys.stdin.readline().split(" ")
        num = int(num)

        if (op == "a"):
            median.add(num)
        elif (op == "r"):
            if (not median.remove(num)):
                print(WRONG_MESSAGE)
                continue

        result = median.median()
        print(format_result(result))


if __name__ == '__main__':
    main()
