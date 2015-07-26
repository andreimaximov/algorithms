#!/usr/bin/env python

import sys
import queue

class Vertex:
    def __init__(self):
        self.edges = {}

    def get_edges(self):
        return self.edges

    def add_edge(self, value, distance):
        if not value in self.edges or distance < self.edges[value]:
            self.edges[value] = distance

class Graph:
    def __init__(self, N):
        self.vertices = {}
        while (N > 0):
            self.vertices[N] = Vertex()
            N -= 1

    def get_vertices(self):
        return self.vertices

    def get_vertex(self, value):
        return self.vertices[value]

    def add_vertex(self, value, vertex):
        self.vertices[value] = vertex

class Dijkstra:
    def __init__(self, graph):
        self.graph = graph

    def calculate(self, start):
        solved = {start: 0}
        adjacents = queue.PriorityQueue()
        self.update_adjacents(start, solved, adjacents)
        while not adjacents.empty():
            (distance, value) = adjacents.get();
            if value in solved:
                continue
            solved[value] = distance
            self.update_adjacents(value, solved, adjacents)
        return solved

    def update_adjacents(self, parent, solved, adjacents):
        for value, distance in self.graph.get_vertex(parent).get_edges().items():
            adjacents.put((solved[parent] + distance, value))

def read_integers():
    return [int (x) for x in sys.stdin.readline().split(" ")]

def build_graph(N, M):
    graph = Graph(N)
    while (M > 0):
        (x, y, R) = read_integers()
        graph.get_vertex(x).add_edge(y, R)
        graph.get_vertex(y).add_edge(x, R)
        M -= 1
    return graph

def print_distances(distances, N, S):
    for i in range(1, N + 1):
        if (i == S):
            continue
        distance = -1 if not i in distances else distances[i]
        print(distance, end = " ")
    print()

def execute_test_case():
    (N, M) = read_integers()
    graph = build_graph(N, M)
    dijkstra = Dijkstra(graph)
    S = int(sys.stdin.readline())
    distances = dijkstra.calculate(S)
    print_distances(distances, N, S)

def main():
    T = int(sys.stdin.readline())
    while (T > 0):
        execute_test_case()
        T -= 1

if __name__ == "__main__":
    main()
