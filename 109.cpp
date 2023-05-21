#include <iostream>
#include <vector>
#include <stack>

using namespace std;
bool flag = false;

void dfs(int v1, int v2, vector<int>& path, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[v1] = true;

    if (v1 == v2) {
        path.push_back(v1);
        flag = true;
        return;
    }

    for (int i = 0; i < graph[v1].size(); i++) {
        int u = graph[v1][i];
        if (!visited[u]) {
            dfs(u, v2, path, graph, visited);
            if (flag) {
                path.push_back(v1);
                return;
            }
        }
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
    vector<int> path;
    dfs(start - 1, end - 1, path, graph, visited);

    if (flag) {
        cout << path.size() - 1 << endl;
        for (int i = path.size() - 1; i >= 0; i--) cout << path[i] + 1<< " ";
    }
    else {
        cout << -1 << endl;
    }
    return 0;
}

