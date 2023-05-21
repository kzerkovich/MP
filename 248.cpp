#include <iostream>
#include <vector>


using namespace std;

struct point {
	int num;
	pair <int, int> coord;
};

/*
void mySort( vector <point> &vec, int size) {
	int middle = size / 2;
	int i = 0, j = size - 1;

	while (i <= j) {
		while (vec[i].coord.first < vec[middle].coord.first) {
			i++;
		}

		while (vec[j].coord.first > vec[middle].coord.first) {
			j--;
		}

		if (i <= j) {
			if (vec[i].coord.first != vec[j].coord.first) {
				swap(vec[i], vec[j]);
			}
			else
				if (vec[i].coord.second > vec[j].coord.second)
					swap(vec[i], vec[j]);
			i++;
			j--;
		}
	}

	if (j > 0) {
		mySort(vec, j + 1);
	}
	if (i < size) {
		mySort(vec, size - i);
	}
} */

void merge(vector<point> &vec, int p, int q, int r) {

	int n1 = q - p + 1;
	int n2 = r - q;

	vector<point> L(n1), M(n2);

	for (int i = 0; i < n1; i++)
		L[i] = vec[p + i];
	for (int j = 0; j < n2; j++)
		M[j] = vec[q + 1 + j];

	int i, j, k;
	i = 0;
	j = 0;
	k = p;

	while (i < n1 && j < n2) {
		if (L[i].coord.first != M[j].coord.first) {
			if (L[i].coord.first <= M[j].coord.first) {
				vec[k] = L[i];
				i++;
			}
			else {
				vec[k] = M[j];
				j++;
			}
		}
		else {
			if (L[i].coord.second <= M[j].coord.second) {
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

void mergeSort(vector<point> &vec, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(vec, l, m);
		mergeSort(vec, m + 1, r);

		merge(vec, l, m, r);
	}
}

int main() {
	int n; cin >> n;

	vector<point> vec(n);

	for (int i = 0; i < n; i++) {
		vec[i].num = i + 1;
		cin >> vec[i].coord.first >> vec[i].coord.second;
	}

	mergeSort(vec, 0, vec.size() - 1);

	for (int i = 0; i < n; i++) {
		cout << vec[i].num << " ";
	}
}