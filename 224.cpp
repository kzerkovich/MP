#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int N, M, K;
	cin >> N >> M;
	vector<int> first(N);
	vector<int> second(M);

	for (int i = 0; i < N; i++) {
		cin >> first[i];
	}

	for (int i = 0; i < M; i++) {
		cin >> second[i];
	}

	sort(first.begin(), first.end());
	set <int> result;
	for (int i = 0; i < M; i++) {
		int left = 0;
		int right = N - 1;
		while (left <= right)
		{
			int middle = (left + right) / 2;
			if (first[middle] == second[i])
				result.insert(second[i]);
			if (first[middle] < second[i])
				left = middle + 1;
			else
				right = middle - 1;
		}

	}

	K = result.size();
	cout << K << endl;

	for (auto i: result) {
		cout << i << " ";
	}
}


/*6 8
1 2 5 2 7 3
9 3 4 2 2 1 9 7
*/