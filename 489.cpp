#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double mySqrt(pair<int, int> pair, double x, double y) {
	double len = 0.0;
	len = sqrt(pow((x - pair.first), 2) + pow((y - pair.second), 2));
	return len;
}

double sumLength(vector<pair<int, int>> vec, double x, double y) {
	double sum = 0.0;
	for (int i = 0; i < vec.size(); i++) {
		sum += mySqrt(vec[i], x, y);
	}
	return sum;
}

int main() {
	int n, x, y;
	cin >> n;
	vector<pair<int, int>> vec(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		vec[i] = { x, y };
	}
	double max_x = 10000.0;
	double min_x = -10000.0;
	int i = 0;
	double mid1_x = 0.0, mid2_x = 0.0, res_y = 0.0;
	while (i < 60) {
		double max_y = 10000.0;
		double min_y = -10000.0;
		double  mid1_y = 0.0, mid2_y = 0.0;
		int j = 0;
		mid1_x = min_x + (max_x - min_x) / 3.0;
		while (j < 60) {
			mid1_y = min_y + (max_y - min_y) / 3.0;
			mid2_y = max_y - (max_y - min_y) / 3.0;
			if (sumLength(vec, mid1_x, mid1_y) < sumLength(vec, mid1_x, mid2_y)) {
				max_y = mid2_y;
			}
			else {
				min_y = mid1_y;
			}
			j++;
		}
		double min_fy = min_y;
		mid2_x = max_x - (max_x - min_x) / 3.0;
		max_y = 10000.0;
		min_y = -10000.0;
		j = 0;
		mid1_y = 0.0, mid2_y = 0.0;
		while (j < 60) {
			mid1_y = min_y + (max_y - min_y) / 3.0;
			mid2_y = max_y - (max_y - min_y) / 3.0;
			if (sumLength(vec, mid2_x, mid1_y) < sumLength(vec, mid2_x, mid2_y)) {
				max_y = mid2_y;
			}
			else{
				min_y = mid1_y;
			}
			j++;
		}
		double min_sy = min_y;
		if (sumLength(vec, mid1_x, min_fy) < sumLength(vec, mid2_x, min_sy)) {
			max_x = mid2_x;
			res_y = min_fy;
		}
		else {
			min_x = mid1_x;
			res_y = min_sy;
		}
		i++;

	}
	cout << min_x << " " << res_y;
}
