#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int INF = 1e9;

void FloydsAlgorithm(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				matrix[j][k] = min(matrix[j][k], matrix[j][i] + matrix[i][k]);
			}
		}
	}
}



int main() {
	int n; cin >> n;

	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) matrix[i] = new int[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
			if (matrix[i][j] == 0) matrix[i][j] = INF;
		}
	}


	FloydsAlgorithm(matrix, n);

	cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == INF) {
				cout << 0 << " ";
			}
			else {
				cout << matrix[i][j] << " ";
			}
		}
		cout << endl;
	}
}