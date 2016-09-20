#!/usr/bin/env python


class MaxStack(object):
    def __init__(self):
        self._stack = []

    def push(self, value):
        """
        Inserts a value into the stack and updates that maximum value.
        """
        # Use value as max if the stack is empty. Otherwise get larger of
        # current max and this value.
        _max = value if len(self) == 0 else max(value, self.max())
        self._stack.append((value, _max))

    def pop(self):
        """
        Removes and returns the top value in the stack.
        """
        return self._stack.pop()[0]

    def max(self):
        """
        Returns the largest value in the stack.
        """
        assert len(self) > 0
        return self._stack[-1][1]

    def __len__(self):
        return len(self._stack)


class MaxQueue(object):
    """
    Monotonic FIFO queue that keeps track of the maximum of its values.
    """
    def __init__(self):
        self._inbox = MaxStack()
        self._outbox = MaxStack()

    def offer(self, value):
        self._inbox.push(value)

    def poll(self):
        """
        Removes the returns the next value in the queue. O(1) amortized.
        """
        if len(self._outbox) == 0:
            # If the outbox is empty we need to move all values from the inbox
            # to the outbox. Since both are stacks, we are doing a double
            # reversal and getting a FIFO order when popping from outbox.
            while len(self._inbox) > 0:
                self._outbox.push(self._inbox.pop())
        return self._outbox.pop()

    def max(self):
        """
        Returns the largest value in the queue. O(1)
        """
        n = len(self._inbox)
        m = len(self._outbox)
        assert n > 0 or m > 0
        if n == 0:
            return self._outbox.max()
        elif m == 0:
            return self._inbox.max()
        # Get largest in inbox and outbox if both have values.
        return max(self._outbox.max(), self._inbox.max())


class Solution(object):
    def maxSlidingWindow(self, values, k):
        """
        Returns the maximum value in each window of length k in values. Runtime
        is O(N) for N values.

        :type values: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(values)
        assert k <= n

        if k == 0:
            return []

        # Populate queue with first K - 1 values.
        mq = MaxQueue()
        for i in xrange(0, k - 1):
            mq.offer(values[i])

        # Get the maximum for the next N - K + 1 windows. In each iteration
        # the queue has K - 1 of the last values so we just add the current one
        # at index j before getting the max. Then we pop the first value in the
        # window to maintain a queue of the last K - 1 nodes for the next
        # iteration.
        maxes = []
        for i in xrange(k - 1, n):
            mq.offer(values[i])
            maxes.append(mq.max())
            mq.poll()
        return maxes


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/sliding-window-maximum/')

if __name__ == '__main__':
    main()
