#!/usr/bin/env python

import sys
from queue import Queue


def read_ints():
    return [int(x) for x in sys.stdin.readline().split(" ")]


def build_graph(N, M):
    node_edges = [0]
    while (N > 0):
        node_edges.append([])
        N -= 1
    while (M > 0):
        (x, y) = read_ints()
        node_edges[x].append(y)
        node_edges[y].append(x)
        M -= 1
    return node_edges


def compute_distances(S, node_edges):
    distances = {S: 0}
    queue = Queue()
    queue.put(S)
    while (not queue.empty()):
        element = queue.get()
        distance = distances[element] + 6
        for neighbor in node_edges[element]:
            if (neighbor in distances):
                continue
            distances[neighbor] = distance
            queue.put(neighbor)
    return distances


def print_distances(S, N, distances):
    for i in range(1, N + 1):
        if (i == S):
            continue
        if i in distances:
            print(distances[i], end=" "),
        else:
            print(-1, end=" "),
    print()


def test_case():
    (N, M) = read_ints()
    node_edges = build_graph(N, M)
    S = int(sys.stdin.readline())
    distances = compute_distances(S, node_edges)
    print_distances(S, N, distances)


def main():
    T = int(sys.stdin.readline())
    while (T > 0):
        test_case()
        T -= 1

if __name__ == '__main__':
    main()
