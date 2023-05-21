#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> g[MAXN], gr[MAXN];
bool used[MAXN];
int comp[MAXN];
stack<int> st;

void dfs1(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs1(to);
        }
    }
    st.push(v);
}

void dfs2(int v, int color) {
    comp[v] = color;
    for (int to : gr[v]) {
        if (comp[to] == 0) {
            dfs2(to, color);
        }
    }
}
int color = 0;
void kosaraju() {
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (comp[v] == 0) {
            color++;
            dfs2(v, color);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        gr[v].push_back(u);
    }
    kosaraju();

    cout << color << endl;

    for (int i = 1; i <= n; i++) {
        cout << comp[i] << " ";
    }
    return 0;
}