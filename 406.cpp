#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	double s, m, p; cin >> s >> m >> p;
	double percent = p / 100.0 + 1.0;
	double sumPr = 0.0;

	for (int i = 0; i < m; i++)
		sumPr += pow(percent, (m - (double)i - 1.0));
	double min = 0.0;
	double max = 10000000.0;
	double mid = 0.0;
	for (int i = 0; i < 40; i++) {
		mid = (min + max) / 2.0;
		if (s * pow(percent, m) - sumPr * mid < 0.0) {
			max = mid;
		}
		else
			min = mid;
	}
	cout << setprecision(10);
	cout << mid;
}