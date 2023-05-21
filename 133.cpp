#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct heap {
  int num, count;
};


void my_swap(vector<heap> &, int, int);
vector<heap> order;

void lift_up(vector<heap> &vec, int n) {
  int k = (n - 1) / 2;
  if (vec[n].num < vec[k].num) {
    my_swap(vec, k, n);
    lift_up(vec, k);
  }
}

void lift_down(vector<heap> &vec, int n) {
  int k = 2 * n + 1;
  int end = vec.size();
  while (k < end - 1) {
    if (vec[k].num > vec[k + 1].num)
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

void my_swap(vector<heap> &vec, int a, int b) {
  swap(order[vec[a].count], order[vec[b].count]);
  swap(vec[a], vec[b]);
}

int main() {
  int n;
  cin >> n;
  order = vector<heap>(n);
  vector<heap> heaper;
  vector<int> result;

  string str, res;

  int count = 0;
  for (int i = 0; i < n; i++) {
    cin >> str;

    if ('A' == str[0]) {
      int num = stoi(str.substr(4, str.size() - 1));
      heaper.push_back(heap{num, count});
      order[count].num = num;
      order[count].count = heaper.size() - 1;
      lift_up(heaper, heaper.size() - 1);
      count++;
    }

    if ('D' == str[0]) {
      int num = stoi(str.substr(4, str.size() - 1)) - 1;
      int to_del = order[num].count;
      int last = heaper.size() - 1;
      my_swap(heaper, to_del, last);
      heaper.pop_back();
      if (to_del < heaper.size())
        lift_down(heaper, to_del);
    }

    if ('F' == str[0]) {
      int num = stoi(str.substr(5, str.size() - 1)) - 1;
      int e = min(32, (int)(heaper.size()));
      vector<int> help(e);
      for (int i = 0; i < e; i++) {
        help[i] = heaper[i].num;
      }
      sort(help.begin(), help.end());
      result.push_back(help[num]);
    }
  }
  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << endl;
  }
}