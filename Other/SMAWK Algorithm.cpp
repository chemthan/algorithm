#include <bits/stdc++.h>
using namespace std;

/*
* SMAWK algorithm
* Find row minimal for a totally monotone matrix a[][] in linear time
* Matrix a[][] is totally monotone iff for any 0 <= i1 < i2 < n, 0 <= j1 < j2 < m
* a[i2][j1] < a[i2][j2] => a[i1][j1] < a[i1][j2]
* a[i2][j1] = a[i2][j2] => a[i1][j1] <= a[i1][j2]
*/

int a[9][18] = {
	{25, 21, 13, 10, 20, 13, 19, 35, 37, 41, 58, 66, 82, 99, 124, 133, 156, 178},
	{42, 35, 26, 20, 29, 21, 25, 37, 36, 39, 56, 64, 76, 91, 116, 125, 146, 164},
	{57, 48, 35, 28, 33, 24, 28, 40, 37, 37, 54, 61, 72, 83, 107, 113, 131, 146},
	{78, 65, 51, 42, 44, 35, 38, 48, 42, 42, 55, 61, 70, 80, 100, 106, 120, 135},
	{90, 76, 58, 48, 49, 39, 42, 48, 39, 35, 47, 51, 56, 63, 80, 86, 97, 110},
	{103, 85, 67, 56, 55, 44, 44, 49, 39, 33, 41, 44, 49, 56, 71, 75, 84, 96},
	{123, 105, 86, 75, 73, 59, 57, 62, 51, 44, 50, 52, 55, 59, 72, 74, 80, 92},
	{142, 123, 100, 86, 82, 65, 61, 62, 50, 43, 47, 45, 46, 46, 58, 59, 65, 73},
	{151, 130, 104, 88, 80, 59, 52, 49, 37, 29, 29, 24, 23, 20, 28, 25, 31, 39}
};

int lookup(int i, int j) {
	return a[i][j];
}

void SMAWK(int n, int inc, vector<int> col, int row_minima[]) {
	const int row_size = (n + inc - 1) / inc;
	vector<int> sub_col;
	for (int i = 0; i < col.size(); i++) {
		while (sub_col.size() && lookup(inc * (sub_col.size() - 1), sub_col.back()) >= lookup(inc * (sub_col.size() - 1), col[i]))
			sub_col.pop_back();
		if (sub_col.size() < row_size) sub_col.push_back(col[i]);
	}
	col = sub_col;
	//assert(col.size() <= row_size);
	//assert(col.size());
	if (row_size == 1) {
		row_minima[0] = col[0];
		return;
	}
	SMAWK(n, inc << 1, col, row_minima);
	for (int i = inc, c = 0; i < n; i += 2 * inc) {
		int pre = row_minima[i - inc];
		int next = (i + inc < n) ? row_minima[i + inc] : col.back();
		while (c < col.size() && col[c] < pre) c++;
		//assert(c < col.size() && col[c] >= pre);
		//assert(col[c] <= next);
		int& res = row_minima[i];
		res = col[c];
		while (c < col.size() && col[c] <= next) {
			if (lookup(i, col[c]) <= lookup(i, res)) res = col[c];
			c++;
		}
		c--;
	}
}

void SMAWK(int n, int m, int row_minima[]) {
	vector<int> col(m);
	for (int i = 0; i < m; i++) col[i] = i;
	for (int i = 0 ; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << lookup(i, j) << " \n"[j == m - 1];
		}
	}
	SMAWK(n, 1, col, row_minima);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			assert(lookup(i, row_minima[i]) <= lookup(i, j));
		}
	}
}

int main() {
	int best[9];
	SMAWK(9, 18, best);
	return 0;
}
