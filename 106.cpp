#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int timer = 0;
vector<vector<int>> gr;
vector<int> tin, fup;
set<int> points_of_connectebility;
vector<bool> used;

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (auto u : gr[v]) {
        if (u == p) {
            continue;
        }
        if (used[u]) {
            fup[v] = min(fup[v], tin[u]);
        }
        else {
            dfs(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[u] >= tin[v] && p != -1) {
                points_of_connectebility.insert(v + 1);
            }
            children++;
        }
    }
    if (p == -1 && children > 1) {
        points_of_connectebility.insert(v + 1);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    gr.resize(n);
    tin.resize(n);
    fup.resize(n);
    used.resize(n);
    int v, u;
    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        v--;
        u--;
        gr[v].push_back(u);
        gr[u].push_back(v);
    }

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);

    cout << points_of_connectebility.size() << endl;
    for (auto i : points_of_connectebility) {
        cout << i << " ";
    }
}