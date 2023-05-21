#include <iostream>
#include <vector>
using namespace std;

struct edges {
	int v1, v2, weight;
};

int main() {
	int INF = 1e9;

	int n, m;
	cin >> n >> m;

	vector<edges> edge;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edge.push_back({ u - 1, v - 1, w });
	}

	vector<int> result(n, INF);
	result[0] = 0;

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			if (result[edge[j].v1] != INF && result[edge[j].v2] > result[edge[j].v1] + edge[j].weight)
				result[edge[j].v2] = result[edge[j].v1] + edge[j].weight;
		}
	}

	cout << endl;

	for (int i = 1; i < n; i++) {
		if (result[i] == INF) {
			cout << "NO" << endl;
		}
		else
			cout << result[i] << endl;
	}

	return 0;
}