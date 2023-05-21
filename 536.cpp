#include <iostream>
#include <string>
#include <vector>

using namespace std;
long long mod = 30000000;

long long hash_fun_1(string& str) {
	long long sum = 0, p = 1;
	for (int i = 0; i < str.size(); i++) {
		sum += (str[i] * p) % mod;
		p = (p * 50) % mod;
	}
	return sum % mod;
}
long long hash_fun_2(string& str) {
	long long sum = 0, p = 1;
	for (int i = 0; i < str.size(); i++) {
		sum += (str[i] * p) % mod;
		p = (p * 79) % mod;
	}
	return sum % mod;
}
long long hash_fun_3(string& str) {
	long long sum = 0, p = 1;
	for (int i = 0; i < str.size(); i++) {
		sum += (str[i] * p) % mod;
		p = (p * 48) % mod;
	}
	return sum % mod;
}
long long hash_fun_4(string& str) {
	long long sum = 0, p = 1;
	for (int i = 0; i < str.size(); i++) {
		sum += (str[i] * p) % mod;
		p = (p * 73) % mod;
	}
	return sum % mod;
}
long long hash_fun_5(string& str) {
	long long sum = 0, p = 1;
	for (int i = 0; i < str.size(); i++) {
		sum += (str[i] * p) % mod;
		p = (p * 45) % mod;
	}
	return sum % mod;
}
long long hash_fun_6(string& str) {
	long long sum = 0, p = 1;
	for (int i = 0; i < str.size(); i++) {
		sum += (str[i] * p) % mod;
		p = (p * 62) % mod;
	}
	return sum % mod;
}


int main() {
	long long n; cin >> n;
	vector<bool> vec(30000000);

	string ent;

	for (int i = 0; i < n; i++) {
		cin >> ent;
		string hk = ent.substr(1, ent.size() - 1);
		long long k1 = hash_fun_1(hk);
		long long k2 = hash_fun_2(hk);
		long long k3 = hash_fun_3(hk);
		long long k4 = hash_fun_4(hk);
		long long k5 = hash_fun_5(hk);
		long long k6 = hash_fun_6(hk);
		if (ent[0] == '+') {
			vec[k1] = 1;
			vec[k2] = 1;
			vec[k3] = 1;
			vec[k4] = 1;
			vec[k5] = 1;
			vec[k6] = 1;
		}
		else cout << (vec[k1] & vec[k2] & vec[k3] & vec[k4] & vec[k5] & vec[k6]);
	}
}