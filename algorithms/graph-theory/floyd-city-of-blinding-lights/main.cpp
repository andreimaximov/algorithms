#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> build_graph(int N, int M)
{
    vector<vector<int>> graph(N, vector<int>(N, -1));
    int x, y, r;
    while (M--) {
        scanf("%d%d%d", &x, &y, &r);
        graph[--x][--y] = r;
    }
    while (N--) {
        graph[N][N] = 0;
    }
    return graph;
}

void floyd_warshall(vector<vector<int>> &graph, int N)
{
    int candidate;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (graph[j][i] == -1 || graph[i][k] == -1) {
                    continue;
                }
                candidate = graph[j][i] + graph[i][k];
                if (candidate < graph[j][k] || graph[j][k] == -1) {
                    graph[j][k] = candidate;
                }
            }
        }
    }
}

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    vector<vector<int>> graph = build_graph(N, M);
    floyd_warshall(graph, N);
    int Q, a, b;
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", graph[--a][--b]);
    }
    return 0;
}
