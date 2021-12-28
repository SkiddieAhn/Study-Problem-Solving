#include <iostream>
#include <vector>
#define MAX 1000001
using namespace std;

int n, k; // size of array, size of color

vector<int> arr; // array with k color
vector<int> color1; // p' color check array
vector<int> color2; // p-p' color check array 

int nclr1, nclr2; // not duplicated color num of color1, color2

int find_min_dr() {
	nclr1 = 0; // initial nclr1 is 0;
	nclr2 = k; // initial nclr2 is k;

	int l, r; // left, right idx of arr => p' array
	l = 1; r = 0;

	int min_size = MAX; // answer candidate

	// find double rainbow and min size of p'
	while (l <= n && r <= n) {
		// fill all elements of color1
		if (nclr1 == k) {
			// fill all elements of color2
			if (nclr2 == k) {
				int size = r - l +1;
				if (size < min_size)
					min_size = size;
			}
			// update l and variables, arrays
			l++;
			if (l > r)
				break;
			color1[arr[l-1]]--;
			if (color1[arr[l-1]] == 0)
				nclr1--;
			if (color2[arr[l-1]] == 0)
				nclr2++;
			color2[arr[l-1]]++;
		}
		else {
			// update r and variables, arrays
			r++;
			if (r > n)
				break;
			color2[arr[r]]--;
			if (color2[arr[r]] == 0)
				nclr2--;
			if (color1[arr[r]] == 0)
				nclr1++;
			color1[arr[r]]++;
		}
	}

	// can't find double rainbow
	if (min_size == MAX)
		return 0;
	// find double rainbow
	else
		return min_size;
}

int main() {
	cin >> n >> k;

	// init
	arr.assign(n+1, 0);
	color1.assign(k + 1, 0);
	color2.assign(k + 1, 0);

	// fill arr, color2
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		arr[i]=num;
		color2[num]++;
	}

	// find min size of p' with double rainbow
	cout << find_min_dr() << endl;

	return 0;
}

