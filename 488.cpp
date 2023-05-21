#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct index {
	int num;
	pair<int, int> pairs;
	double sum;
};

double sumElem(pair<int, int> da, double x) {
	return double(x * da.second - da.first);
}

double sumPair(vector<index> &vec, double x, int k) {
	double sum = 0.0;
	for (int i = 0; i < k; i++) {
		sum += sumElem(vec[i].pairs, x);
	}
	return sum;
}

void merge(vector<index> &vec, int p, int q, int r) {

	int n1 = q - p + 1;
	int n2 = r - q;
	vector<index> L(n1), M(n2);
	for (int i = 0; i < n1; i++)
		L[i] = vec[p + i];
	for (int j = 0; j < n2; j++)
		M[j] = vec[q + 1 + j];
	int i, j, k;
	i = 0; j = 0; k = p;
	while (i < n1 && j < n2) {
			if (L[i].sum < M[j].sum) {
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

void mergeSort(vector<index> &vec, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(vec, l, m);
		mergeSort(vec, m + 1, r);

		merge(vec, l, m, r);
	}
}


int main() {
	int n, k; cin >> n >> k;
	vector<index> vec(n);

	for (int i = 0; i < n; i++) {
		cin >> vec[i].pairs.first >> vec[i].pairs.second;
		vec[i].num = i;
		vec[i].sum = 0.0;
	}

	double min = 0.0;
	double max = 10e5;
	double mbSum = 0.0;
	double mid = 0.0;
	double res = 0.0;
	int i = 0;
	while (i < 40) {
		mid = (max + min) / 2.0;
		for (int i = 0; i < n; i++) {
			vec[i].sum = sumElem(vec[i].pairs, mid);
		}
		mergeSort(vec, 0, n - 1);

		mbSum = sumPair(vec, mid, k);
		if (mbSum < 0.0) {
			res = mid;
			min = mid;
		}
		else {
			max = mid;
		}
		i++;
	}

	cout << setprecision(10);
	cout << res << endl;
	for (int i = 0; i < k; i++)
		cout << vec[i].num + 1 << " ";
}