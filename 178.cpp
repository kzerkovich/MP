#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <limits.h>

using namespace std;

struct three {
    int x, y;
    string w;
};

int INF = INT_MAX;

int row[] = { -1, 0, 0, 1, -1, -1, 1, 1 };
int col[] = { 0, -1, 1, 0, -1, 1, -1, 1 };

int a, b, c, d;

bool isSafe(vector<vector<int>>& field, vector<vector<bool>>& visited, int x, int y) {
    return field[x][y] != 0 && !visited[x][y];
}

bool isValid(int x, int y, int M, int N) {
    return (x < M && y < N) && (x >= 0 && y >= 0);
}

void BFS(vector<vector<int>>& field)
{
    int N = field.size();
    int M = field[0].size();

    vector<vector<int>> dist;
    dist.resize(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
        }
    }
    dist[a - 1][b - 1] = 0;

    vector<vector<bool>> visited;
    visited.resize(N, vector<bool>(M, false));

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    pq.push(make_pair(0, make_pair(a - 1, b - 1)));

    while (!pq.empty())
    {
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        pq.pop();

        if (visited[i][j]) continue;
        visited[i][j] = true;

        for (int k = 0; k < 8; k++)
        {
            int count = 0;
            int new_x = i + row[k];
            int new_y = j + col[k];
            if (isValid(new_x, new_y, N, M) && isSafe(field, visited, new_x, new_y)) {
                if (field[i][j] == 2 && field[new_x][new_y] == 2) continue;
                if (field[new_x][new_y] == 2) count = 1;

                if (dist[i][j] + count < dist[new_x][new_y]) {
                    dist[new_x][new_y] = dist[i][j] + count;
                    pq.push(make_pair(dist[new_x][new_y], make_pair(new_x, new_y)));
                }
            }
        }
    }

    if (dist[c - 1][d - 1] == INF) {
        cout << -1;
    }
    else 
        cout << dist[c - 1][d - 1];
}


int main() {
    int n, m, k;
    vector<vector<int>> matrix;
    while (cin >> n >> m >> a >> b >> c >> d >> k) {
        matrix.clear();
        matrix.resize(n, vector<int>(m));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) matrix[i][j] = 1;

        vector<pair<pair<int, int>, string>> blocks(k);

        for (int i = 0; i < k; i++) {
            int fir, sec;
            string let;
            cin >> fir >> sec >> let;
            blocks[i] = make_pair(make_pair(fir, sec), let);
        }

        for (int i = 0; i < k; i++) {
            int x = blocks[i].first.first - 1;
            int y = blocks[i].first.second - 1;
            matrix[x][y] = 0;
        }

        for (int i = 0; i < k; i++) {
            int x = blocks[i].first.first - 1;
            int y = blocks[i].first.second - 1;
            string let = blocks[i].second;
            if (let == "u") {
                for (int i = x - 1; i >= 0; i--)
                    if (matrix[i][y] != 0) {
                        matrix[i][y] = 2;
                    }
                    else break;
            }

            if (let == "d") {
                for (int i = x + 1; i < n; i++)
                    if (matrix[i][y] != 0) {
                        matrix[i][y] = 2;
                    }
                    else break;
            }

            if (let == "l") {
                for (int i = y - 1; i >= 0; i--)
                    if (matrix[x][i] != 0) {
                        matrix[x][i] = 2;
                    }
                    else break;
            }

            if (let == "r") {
                for (int i = y + 1; i < m; i++)
                    if (matrix[x][i] != 0) {
                        matrix[x][i] = 2;
                    }
                    else break;
            }
        }
        
        BFS(matrix);
        cout << endl;
    }
}
