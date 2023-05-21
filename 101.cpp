#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
	int V;

	list<int>* adj;

	void topologicalSortUtil(int v, bool visited[], stack<int>& Stack) {
		visited[v] = true;

		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
			if (!visited[*i])
				topologicalSortUtil(*i, visited, Stack);

		Stack.push(v);
	};
public:
	Graph(int V) {
		this->V = V;
		adj = new list<int>[V];
	};

	void addEdge(int v, int w) {
		adj[v].push_back(w);
	};

	void topologicalSort() {
		stack<int> Stack;

		bool* visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;

		for (int i = 0; i < V; i++)
			if (visited[i] == false)
				topologicalSortUtil(i, visited, Stack);

		while (!Stack.empty()) {
			cout << Stack.top() + 1 << " ";
			Stack.pop();
		}
	};
};

int main()
{
	int n;
	int edge;
	cin >> n;

	Graph graph(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> edge;
			if (edge == 1)
				graph.addEdge(i, j);
		}
	}

	graph.topologicalSort();

	return 0;
}