#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
bool visited[MAXN];
int tin[MAXN], low[MAXN];
int timer = 0;

map<pair<int, int>, int> edge;
vector<int> result;


void dfs(int u, int p = -1) {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (visited[v]) {
            low[u] = min(low[u], tin[v]);
        }
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                auto iter = edge.find(make_pair(u, v));
                if (iter != edge.end())
                    result.push_back(edge[make_pair(u, v)]);
                else {
                    result.push_back(edge[make_pair(v, u)]);
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge[make_pair(u, v)] = i + 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    cout << result.size() << endl;

    sort(result.begin(), result.end());

    for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
    return 0;
}