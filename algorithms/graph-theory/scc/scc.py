#!/usr/bin/env python


class Graph(object):
    def __init__(self, n):
        """Creates a directed graph with n nodes."""
        self.edges = [[] for _ in range(n)]

    def add_edge(self, u, v):
        """Creates an edge from u -> v."""
        self.edges[u].append(v)


def reverse(G):
    """Creates a reverse of the graph G."""
    n = len(G.edges)
    Gr = Graph(n)
    for u in range(n):
        for v in G.edges[u]:
            Gr.add_edge(v, u)
    return Gr


def topological(G):
    """Returns a topological ordering of nodes in the graph."""
    n = len(G.edges)
    visited = [False] * n
    ordering = []

    def dfs(u):
        visited[u] = True
        for v in G.edges[u]:
            if not visited[v]:
                dfs(v)
        ordering.append(u)

    for u in range(0, n):
        if not visited[u]:
            dfs(u)

    ordering.reverse()
    return ordering


def scc(G):
    """Calculates a list of SCC for the graph.

    Args:
        G (Graph): The directed graph

    Returns:
        List[Set[int]]: List of SCC's where each SCC is a set of nodes.
    """
    Gr = reverse(G)
    topo = topological(Gr)

    n = len(G.edges)
    visited = [False] * n

    # Runs DFS on G starting at u and gathers all connected vertices into an
    # SCC set.
    def dfs(u, scc):
        visited[u] = True
        scc.add(u)
        for v in G.edges[u]:
            if not visited[v]:
                dfs(v, scc)
        return scc

    # Start at the sinks of G (Sources of Gr) and peel SCC's.
    sccs = []
    for u in topo:
        if not visited[u]:
            sccs.append(dfs(u, set()))

    sccs.reverse()
    return sccs


def main():
    g = Graph(10)

    # First SCC
    g.add_edge(0, 1)
    g.add_edge(1, 2)
    g.add_edge(2, 0)

    # Second SCC
    g.add_edge(1, 3)
    g.add_edge(3, 4)
    g.add_edge(4, 3)

    # Third SCC
    g.add_edge(2, 5)
    g.add_edge(5, 6)
    g.add_edge(6, 5)

    # Last SCC
    g.add_edge(4, 7)
    g.add_edge(6, 8)
    g.add_edge(8, 9)
    g.add_edge(9, 7)
    g.add_edge(7, 8)

    # Test algorithm
    result = scc(g)
    expect = [set([0, 1, 2]), set([3, 4]), set([5, 6]), set([7, 8, 9])]
    assert result == expect, 'Expected %s but got %s.' % (expect, result)
    print('Tests pass!')

if __name__ == '__main__':
    main()
