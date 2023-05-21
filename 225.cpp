#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;

int func(vector<int> vec, int max) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += vec[i] / max;
	}
	return sum;
}

int main() {
	int k;
	cin >> n >> k;
	vector<int> vec(n);

	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}

	int max = *max_element(vec.begin(), vec.end());
	vector<int> length(max);

	for (int i = 0; i < max; i++) {
		length[i] = i + 1;
	}

	int left = 0;
	int right = max - 1;
	int res = 0;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (func(vec, length[middle]) >= k) {
			res = length[middle];
			left = middle + 1;
		}
		else
			right = middle - 1;
	}
	cout << res;
}