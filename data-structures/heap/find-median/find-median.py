#!/usr/bin/env python

import sys
import heapq


class Median(object):
    def __init__(self):
        self.min = []
        self.max = []

    def add(self, num):
        if (len(self.max) > len(self.min)):
            if (num >= -self.max[0]):
                heapq.heappush(self.min, num)
            else:
                heapq.heappush(self.min, -heapq.heappop(self.max))
                heapq.heappush(self.max, -num)
        else:
            if (len(self.min) > 0 and num >= self.min[0]):
                heapq.heappush(self.max, -heapq.heappop(self.min))
                heapq.heappush(self.min, num)
            else:
                heapq.heappush(self.max, -num)

    def median(self):
        if (len(self.max) == len(self.min)):
            return (-self.max[0] + self.min[0]) / 2
        else:
            return -self.max[0]


def main():
    N = int(sys.stdin.readline())
    m = Median()
    while (N > 0):
        i = int(sys.stdin.readline())
        m.add(i)
        print(m.median())
        N = N - 1

if __name__ == "__main__":
    main()
