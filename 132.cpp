#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct heap{
	int num;
	string str;
};

void lift_up(vector<heap>& vec, int n) {
	int k = (n - 1) / 2;
		if (vec[n].str > vec[k].str) {
			swap(vec[n], vec[k]);
			lift_up(vec, k);
	}
}


int main() {
	int n; cin >> n;
	vector<heap> h(n);
	string str;
	
	for (int i = 0; i < n; i++) {
		cin >> str;
		h[i].str = str;
		h[i].num = i;
		lift_up(h, i);
	}
	vector<int> k(n);
	for (int i = 0; i < n; i++) {
		k[h[i].num] = i + 1;
	}

	for (int i = 0; i < n; i++) {
			cout << k[i] << endl;
		}
}