#!/usr/bin/env python

import sys
from heapq import *


def read(fn):
    return tuple(fn(i) for i in sys.stdin.readline().split(' '))


def load_graph(N, M):
    """
    Builds an adjacency matrix representation of a graph with N vertices. Each
    graph[i][j] is the length of an edge between vertice i and j. Lengths of -1
    indicate there is no edge between two vertices.

    :rtype: List[List[int]]
    """
    graph = [[-1] * N for i in range(0, N)]

    for i in range(0, M):
        (x, y, r) = read(int)
        x -= 1
        y -= 1
        graph[x][y] = r

    # Zero out edges to self.
    for i in range(0, N):
        graph[i][i] = 0

    return graph


def floyd_warshall(graph):
    """
    Takes an adjacency matrix graph of edge distances and returns a matrix of
    shortest distances between all pairs of vertices. Distances of -1 indicate
    there is no path between a pair of vertices.

    See: http://www.cs.cornell.edu/~wdtseng/icpc/notes/graph_part3.pdf

    :rtype: List[List[int]]
    """
    N = len(graph)
    distances = [list(graph[i]) for i in range(0, N)]

    # After the n-th iteration of the loop, each distances[j][k] contains
    # length of shortest path from j to k through vertices {0...n - 1}
    for i in range(0, N):
        for j in range(0, N):
            for k in range(0, N):
                if distances[j][i] == -1 or distances[i][k] == -1:
                    continue
                # Use vertex i as a mid-point vertex.
                candidate = distances[j][i] + distances[i][k]
                if distances[j][k] == -1 or candidate < distances[j][k]:
                    distances[j][k] = candidate

    return distances


def main():
    (N, M) = read(int)

    graph = load_graph(N, M)
    distances = floyd_warshall(graph)

    Q = read(int)[0]
    for i in range(0, Q):
        (a, b) = read(int)
        a -= 1
        b -= 1
        print(distances[a][b])


if __name__ == '__main__':
    main()
