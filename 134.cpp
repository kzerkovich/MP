#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct three {
	int board, index, color;
};

void my_swap(vector<three>&, int, int);
//vector<pair<int, int>> indexPlusHeap;
map <int, int> test;

bool comp(three first, three second) {
	return (first.board < second.board);
}

void my_swap(vector<three>& vec, int a, int b) {
	swap(test[vec[a].index], test[vec[b].index]);
	swap(vec[a], vec[b]);
}

void lift_up(vector<three>& vec, int n) {
	int k = (n - 1) / 2;
	if (vec[n].index > vec[k].index) {
		my_swap(vec, k, n);
		lift_up(vec, k);
	}
}

void lift_down(vector<three>& vec, int n) {
	int k = 2 * n + 1;
	int end = vec.size();
	while (k < end - 1) {
		if (vec[k].index < vec[k + 1].index)
			k++;
		my_swap(vec, k, n);
		n = k;
		k = 2 * k + 1;
	}
	if (k == end - 1) {
		my_swap(vec, k, n);
		n = k;
	}
	lift_up(vec, n);
}

void deleteE(vector<three>& vec, int n) {
	int k = test[n];
	my_swap(vec, k, vec.size() - 1);
	vec.pop_back();
	if (k < vec.size())
		lift_down(vec, k);
}

int main() {
	int k, n; cin >> k >> n;;
	vector<three> right_border(n);
	vector<three> left_border(n);
	vector<three> heap;
	//indexPlusHeap = vector<pair<int, int>>(n);

	int l, r, c;
	int m = 0;
	int j = 0;

	for (int i = 0; i < n; i++) {
		cin >> l >> r >> c;
		left_border[i] = { l, i, c };
		right_border[i] = { r, i, c };
	}
	sort(right_border.begin(), right_border.end(), comp);
	sort(left_border.begin(), left_border.end(), comp);
	int count = 0;
	for (int i = 0; i < k; i++) {
		for (j; j < left_border.size(); j++) {
			if (left_border[j].board == i) {
				heap.push_back(left_border[j]);
				test[left_border[j].index] = heap.size() - 1;
				//indexPlusHeap[count].first = left_border[j].index;
				//indexPlusHeap[count].second = heap.size() - 1;
				lift_up(heap, heap.size() - 1);
				//count++;
				//sort(indexPlusHeap.begin(), indexPlusHeap.end());
			}
			else break;
		}
		
		for (m; m < right_border.size(); m++) {
			if (right_border[m].board == i) {
				deleteE(heap, right_border[m].index);
			}
			else break;
		}
		if (heap.size() != 0) {
			cout << heap[0].color << " ";
		}
		else
			cout << 0 << " ";
	}
}