#include <iostream>
#include <vector>
#include <queue>

using namespace std;
bool flag = false;

void bfs(int v1, int v2, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(v1);
    vector<int> parent(graph.size());
    visited[v1] = true;
    parent[v1] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < graph[v].size(); ++i) {
            int to = graph[v][i];
            if (!visited[to]) {
                visited[to] = true;
                q.push(to);
                parent[to] = v;
            }
        }
    }
    if (!visited[v2])
        cout << -1;
    else {
        vector<int> path;
        for (int v = v2; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        cout << path.size() - 1 << endl;
        for (size_t i = 0; i < path.size(); ++i)
            cout << path[i] + 1 << " ";
    }
}


int main() {
    int n, start, end;
    cin >> n >> start >> end;
    vector<vector<int>> graph(n);
    vector<bool> visited(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int elem; cin >> elem;
            if (elem == 1) graph[i].push_back(j);
        }
    }

    bfs(start - 1, end - 1, graph, visited);

    return 0;
}

