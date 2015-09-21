#!/usr/bin/env python

import sys
import queue


def read_ints():
    return [int(x) for x in sys.stdin.readline().split()]


def build_graph(I):
    graph = {}
    while (I > 0):
        (A, B) = read_ints()
        if (A not in graph):
            graph[A] = []
        if (B not in graph):
            graph[B] = []
        graph[A].append(B)
        graph[B].append(A)
        I -= 1
    return graph


def traverse(graph, astronaut):
    country_size = 0
    q = queue.Queue()
    q.put(astronaut)
    while (not q.empty()):
        a = q.get()
        if (graph[a] is None):
            continue
        country_size += 1
        edges = graph[a]
        graph[a] = None
        for b in edges:
            q.put(b)
    return country_size


def combinations(graph, N):
    combinations = astronauts = 0
    for a in graph:
        country_size = traverse(graph, a)
        combinations += astronauts * country_size
        astronauts += country_size
    # Each independent astronaut will add {#astronauts} combinations
    combinations += int((astronauts + N - 1) * 0.5 * (N - astronauts))
    return combinations


def main():
    (N, I) = read_ints()
    graph = build_graph(I)
    print(combinations(graph, N))

if __name__ == "__main__":
    main()
