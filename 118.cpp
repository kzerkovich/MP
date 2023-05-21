#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 100005;
const int INF = 1e9;

int n, m;
vector<pair<int, int>> g[MAXN];
bool used[MAXN];
int dist[MAXN];
int parent[MAXN];

void prim(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });
    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();
        if (used[v]) {
            continue;
        }
        used[v] = true;
        for (auto edge : g[v]) {
            int to = edge.first;
            int weight = edge.second;
            if (!used[to] && weight < dist[to]) {
                dist[to] = weight;
                parent[to] = v;
                pq.push({ dist[to], to });
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }
    prim(1);
    int total_weight = 0;
    for (int i = 1; i <= n; i++) {
        total_weight += dist[i];
    }
    cout << total_weight << endl;
    for (int i = 1; i <= n; i++) {
        if (parent[i] != -1) cout << parent[i] << " " << i << endl;
    }

    return 0;
}