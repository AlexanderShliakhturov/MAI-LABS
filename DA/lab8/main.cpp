#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
};

void dijkstra(int n, int start, int finish, const vector<vector<Edge>>& graph) {
    vector<int> dist(n + 1, INF); 
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    if (dist[finish] == INF) {
        cout << "No solution" << endl;
    } else {
        cout << dist[finish] << endl;
    }
}

int main() {
    int n, m, start, finish;
    cin >> n >> m >> start >> finish;

    vector<vector<Edge>> graph(n + 1); 

    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight}); 
    }

    dijkstra(n, start, finish, graph);

    return 0;
}
