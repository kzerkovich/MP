#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& vec, int p, int q, int r) {

	int n1 = q - p + 1;
	int n2 = r - q;

	vector<int> L(n1), M(n2);

	for (int i = 0; i < n1; i++)
		L[i] = vec[p + i];
	for (int j = 0; j < n2; j++)
		M[j] = vec[q + 1 + j];

	int i, j, k;
	i = 0;
	j = 0;
	k = p;

	while (i < n1 && j < n2) {
		if (L[i] <= M[j]) {
			vec[k] = L[i];
			i++;
		}
		else {
			vec[k] = M[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		vec[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		vec[k] = M[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int>& vec, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(vec, l, m);
		mergeSort(vec, m + 1, r);

		merge(vec, l, m, r);
	}
}

int main() {
	int N, M, K;
	cin >> N;
	vector<int> first(N);
	for (int i = 0; i < N; i++) {
		cin >> first[i];
	}

	cin >> M;
	vector<int> second(M);
	for (int i = 0; i < M; i++) {
		cin >> second[i];
	}

	cin >> K;
	vector<int> sorting(K);
	for (int i = 0; i < K; i++) {
		cin >> sorting[i];
	}

	mergeSort(first, 0, N - 1);
	mergeSort(second, 0, M - 1);

	for (int i = 0; i < K; i++) {
		bool word = false;
		for (int j = 0; j < N; j++) {
			int find = sorting[i] - first[j];
			int left = 0;
			int right = M - 1;
			while (left <= right)
			{
				int middle = (left + right) / 2;
				if (second[middle] == find)
					word = true;
				if (second[middle] < find)
					left = middle + 1;
				else
					right = middle - 1;
			}
		}
		if (word) {
			cout << "YES" << endl;
		}
		else
			cout << "NO" << endl;
	}
}