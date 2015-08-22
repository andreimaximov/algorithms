#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct vertex;
struct edge;
struct edge_comparator;

typedef priority_queue<edge, vector<edge>, edge_comparator> edge_queue;

struct vertex
{
    vector<edge> edges;
    bool visited = false;
};

struct edge
{
    int v_index = 0;
    int cost = 0;

    edge(int v_index, int cost) : v_index(v_index), cost(cost) {}
};

struct edge_comparator
{
    bool operator()(edge a, edge b)
    {
        return a.cost > b.cost;
    }
};

void queue_edges(edge_queue &q, vector<vertex> &verticies, vector<edge> &edges)
{
    for (size_t i = 0; i < edges.size(); ++i) {
        if (verticies[edges[i].v_index].visited) {
            continue;
        }
        q.push(edges[i]);
    }
}

int sub_graph(vector<vertex> &verticies, int S)
{
    int cost = 0;

    edge_queue q;
    q.push(edge {S, 0});

    while (!q.empty()) {
        edge e = q.top();
        q.pop();
        if (verticies[e.v_index].visited) {
            continue;
        }
        verticies[e.v_index].visited = true;
        cost += e.cost;
        queue_edges(q, verticies, verticies[e.v_index].edges);
    }

    return cost;
}

int main()
{
    int N, M, x, y, r, S;
    cin >> N >> M;

    vector<vertex> verticies(N + 1);

    for(size_t i = 0; i < M; ++i) {
        cin >> x >> y >> r;
        verticies[x].edges.emplace_back(y, r);
        verticies[y].edges.emplace_back(x, r);
    }

    cin >> S;
    cout << sub_graph(verticies, S) << endl;

    return 0;
}
