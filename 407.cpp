#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	double c, t;
	cin >> c >> t;

	double min = 0.0;
	double max = 2000000000.0;
	double mid = 0.0;
	for (int i = 0; i < 61; i++) {
		mid = (min + max) / 2.0;
		if (c * mid * log2(mid) > t) {
			max = mid;
		}
		else
			min = mid;
	}
	cout << setprecision(20);
	cout << (double)mid;
}