#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

long long int quickSort(long long int arr[], int l, int r, int k)
{
	while (l < r)
	{
		int x = arr[k];
		int i = l;
		int j = r;
		while (i <= j)
		{
			while (arr[i] < x)
				i++;
			while (arr[j] > x)
				j--;
			if (i <= j)
			{
				swap(arr[i], arr[j]);
				i++;
				j--;
			}
		}
		if (j < k)
			l = i;
		if (k < i)
			r = j;
	}

	return arr[k];
}

int main() {
	int n, k, a, b, c, r;
	cin >> n >> k;
	long long int* arr = new long long int[n];
	cin >> arr[0] >> arr[1];
	cin >> a >> b >> c >> r;

	for (int i = 2; i < n; i++) {
		arr[i] = ((a * arr[i - 2] + b * arr[i - 1] + c) % r);
	}
	cout << endl << quickSort(arr, 0, n - 1, k - 1);
}