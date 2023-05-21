#include <iostream>
#include <vector>

using namespace std;

void merge(vector<pair<int, int>>& vec, int p, int q, int r) {

	int n1 = q - p + 1;
	int n2 = r - q;
	vector<pair<int, int>> L(n1), M(n2);
	for (int i = 0; i < n1; i++)
		L[i] = vec[p + i];
	for (int j = 0; j < n2; j++)
		M[j] = vec[q + 1 + j];
	int i, j, k;
	i = 0; j = 0; k = p;
	while (i < n1 && j < n2) {
		if (L[i].first != M[j].first) {
			if (L[i].first < M[j].first) {
				vec[k] = L[i];
				i++;
			}
			else {
				vec[k] = M[j];
				j++;
			}
		}
		else {
			if (L[i].second < M[j].second) {
				vec[k] = L[i];
				i++;
			}
			else {
				vec[k] = M[j];
				j++;
			}
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

void mergeSort(vector<pair<int, int>>& vec, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(vec, l, m);
		mergeSort(vec, m + 1, r);

		merge(vec, l, m, r);
	}
}


int main() {
	int n, l, r;
	cin >> n;
	int k = 2 * n;
	vector<pair<int, int>> vec(k);
	for (int i = 0; i < k; i += 2) {
		cin >> l >> r;
		vec[i].second = -1; vec[i].first = l;
		vec[i + 1].second = 1; vec[i + 1].first = r;
	}
	mergeSort(vec, 0, k - 1);
	
	int count = 0;
	int n_max = 0;

	for (int i = 0; i < k; i++) {
		if (vec[i].second == -1) {
			count++;
		}
		else
			count--;
		if (count > n_max)
			n_max = count;
	}

	int point = 0;
	for (int i = 0; i < k; i++) {
		if (vec[i].second == -1) {
			count++;
		}
		else
			count--;
		if (count == n_max)
			point += vec[i + 1].first - vec[i].first + 1;
	}

	cout << point;
}