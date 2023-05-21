#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
	int n, x, v;
	cin >> n;
	vector<pair<int, int>> vec(n);

	for (int i = 0; i < n; i++) {
		cin >> x >> v;
		vec[i] = { x, v };
	}
	double res_time = 0.0;
	double min_time = 0.0;
	double max_time = 10e9;
	double mid_time = 0.0;
	for (int i = 0; i < 60; i++) {
		mid_time = (max_time + min_time) / 2.0;
		bool boom = false;
		double coord = -10e9;
		for (int j = 0; j < n; j++) {
			if (vec[j].second > 0) {
				if (coord < max(vec[j].first + mid_time * vec[j].second, -10e9))
					coord = vec[j].first + mid_time * vec[j].second;
			}
			else {
				if (coord > max(vec[j].first + mid_time * vec[j].second, -10e9)) {
					boom = true;
					break;
				}
			}
		}
		if (boom) {
			max_time = mid_time;
		}
		else
			min_time = mid_time;
		if (max_time != 10e9) {
			res_time = mid_time;
		}
		else
			res_time = -1;
	}
	cout << setprecision(10);
	cout << res_time;
}
