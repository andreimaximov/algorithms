#!/usr/bin/env python

import sys
import queue


def read_ints():
    return [int(x) for x in sys.stdin.readline().split()]


def build_graph(E):
    graph = {}
    while (E > 0):
        (s1, s2, cost) = read_ints()
        if s1 not in graph:
            graph[s1] = []
        graph[s1].append((s2, cost))
        if s2 not in graph:
            graph[s2] = []
        graph[s2].append((s1, cost))
        E -= 1
    return graph


def next_stations(current, graph, stations_queue, costs_cache):
    for (station, cost) in graph[current]:
        base_cost = costs_cache[current]
        cost = base_cost + max(0, cost - base_cost)
        if (station in costs_cache and costs_cache[station] < cost):
            continue
        stations_queue.put((cost, station))


def calculate(graph, N):
    costs_cache = {1: 0}
    stations_queue = queue.PriorityQueue()
    next_stations(1, graph, stations_queue, costs_cache)
    while not stations_queue.empty():
        (cost, current) = stations_queue.get()
        if (current == N):
            return cost
        if (current in costs_cache):
            continue
        costs_cache[current] = cost
        next_stations(current, graph, stations_queue, costs_cache)


def main():
    (N, E) = read_ints()
    graph = build_graph(E)
    result = calculate(graph, N)
    if (result is None):
        print("NO PATH EXISTS")
    else:
        print(result)

if __name__ == "__main__":
    main()
