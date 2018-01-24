#!/usr/bin/env python

import sys
from heapq import *


def read(fn):
    return tuple(fn(i) for i in sys.stdin.readline().split(' '))


def load_graph(N, M):
    """
    Builds an adjacency list representation of a graph with N vertices. Each
    graph[i][j] is the minimum length of an edge between vertice i and j.

    :rtype List[int, Dict[int, int]]
    """
    graph = [dict() for i in range(0, N)]

    for i in range(0, M):
        (x, y, r) = read(int)
        x -= 1
        y -= 1

        # Ignore all edges except minimum length edge.
        r = r if y not in graph[x] else min(r, graph[x][y])
        graph[x][y] = r
        graph[y][x] = r

    return graph


def dijkstras(graph, source):
    """
    Runs Dijkstras on the graph starting at the source vertex. Returns a list
    of distances from the source to all other nodes. Distance of -1 for a
    vertex i indicates there is no path from source to i.

    :rtype List[int]
    """
    q = []
    heappush(q, (0, source))

    distances = [-1] * len(graph)
    distances[source] = 0

    while len(q) > 0:
        (distance, vertice) = heappop(q)

        # Ignore this distance if a shorter path has been found for this node.
        if distances[vertice] > 0:
            continue
        distances[vertice] = distance

        # Queue up all unvisited neighbors.
        for n in graph[vertice]:
            if distances[n] > -1:
                continue
            cost = distance + graph[vertice][n]
            heappush(q, (cost, n))

    return distances


def test():
    (N, M) = read(int)
    graph = load_graph(N, M)

    S = read(int)[0] - 1
    distances = dijkstras(graph, S)

    for i in range(0, N):
        if i != S:
            end = ' ' if i < N - 1 else '\n'
            print(distances[i], end=end)


def main():
    T = read(int)[0]
    for i in range(0, T):
        test()

if __name__ == '__main__':
    main()
