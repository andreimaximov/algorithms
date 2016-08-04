#!/usr/bin/env python

import sys
from queue import PriorityQueue


class Graph(object):
    """
    Represents a graph using an adjacency list.
    """
    def __init__(self, N):
        self.nodes = [None] * N

    def add_undir_edge(self, x, y, r):
        self.add_dir_edge(x, y, r)
        self.add_dir_edge(y, x, r)

    def add_dir_edge(self, x, y, r):
        if self.nodes[x] is None:
            self.nodes[x] = dict()
        self.nodes[x][y] = r


def load_graph(input):
    """
    Populates a graph using the input stream.
    """
    (N, M) = [int(i) for i in input.readline().split(' ')]
    graph = Graph(N)
    for i in range(0, M):
        (x, y, r) = [int(i) for i in input.readline().split(' ')]
        graph.add_undir_edge(x - 1, y - 1, r)
    return graph


def prims_weight(graph, S):
    """
    Runs Prim's algorithm on the graph and returns the weight of the MST.
    """
    weight = 0
    queue = PriorityQueue()
    queue.put((0, S))
    visited = [False] * len(graph.nodes)
    while queue.qsize() > 0:
        (cost, node) = queue.get()
        if visited[node]:
            continue
        visited[node] = True  # Mark node as visited
        weight += cost  # Increment MST weight
        for neighbor in graph.nodes[node]:  # Enqueue neighbors
            if visited[neighbor]:
                continue
            cost = graph.nodes[node][neighbor]
            queue.put((cost, neighbor))
    return weight


def main():
    graph = load_graph(sys.stdin)
    S = int(sys.stdin.readline())
    weight = prims_weight(graph, S - 1)
    print(weight)


if __name__ == '__main__':
    main()
