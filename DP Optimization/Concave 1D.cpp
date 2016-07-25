#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
* f[j] = min(b[i][j] = d[i] + w[i][j]), 0 <= j < i
* d[i] is computed from f[i] in constant time
* Sufficient condition: w[a][c] + w[b][d] <= w[b][c] + w[a][d], a <= b <= c <= d
* Problem:
* 1. http://codeforces.com/problemset/problem/319/C
*/

const int ar[][18] = {
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

typedef int T;
const T oo = (T) 1e9;
const int MAXN = 100010;
int n, r, c;
T f[MAXN];
T g[MAXN];
int h[MAXN];

T D(int i) {return f[i];}
T W(int i, int j) {return ar[i][j];}
T B(int i, int j) {return D(i) + W(i, j);}
T lookup(int j, int i) {if (!i) return g[j + c]; return B(i + r - 1, j + c);}

void SMAWK(int n, int inc, vector<int> col, int row_minima[]) {
	const int row_size = (n + inc - 1) / inc;
	vector<int> sub_col;
	for (int i = 0; i < col.size(); i++) {
		while (sub_col.size() && lookup(inc * (sub_col.size() - 1), sub_col.back()) >= lookup(inc * (sub_col.size() - 1), col[i]))
			sub_col.pop_back();
		if (sub_col.size() < row_size) sub_col.push_back(col[i]);
	}
	col = sub_col;
	if (row_size == 1) {
		row_minima[0] = col[0];
		return;
	}
	SMAWK(n, inc << 1, col, row_minima);
	for (int i = inc, c = 0; i < n; i += 2 * inc) {
		int pre = row_minima[i - inc];
		int next = (i + inc < n) ? row_minima[i + inc] : col.back();
		while (c < col.size() && col[c] < pre) c++;
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
	SMAWK(n, 1, col, row_minima);
}
void solve() {
	/*for (int a = 0; a < n; a++) {
		for (int b = a; b < n; b++) {
			for (int c = b; c < n; c++) {
				for (int d = c; d < n; d++) {
					assert(W(a, c) + W(b, d) <= W(a, d) + W(b, c));
				}
			}
		}
	}*/
	r = 0, c = 1;
	fill_n(g, n, +oo);
	while (c < n) {
		int p = min(2 * c - r, n - 1);
		SMAWK(p - c + 1, c - r + 1, h + c);
		f[c] = lookup(c - c, h[c]);
		int j = 0;
		for (j = c + 1; j <= p; j++) {
			if (B(j - 1, j) < lookup(j - c, h[j])) {
				f[j] = B(j - 1, j);
				break;
			}
			else {
				f[j] = lookup(j - c, h[j]);
				if (B(j - 1, p) < lookup(p - c, h[p])) {
					for (int k = j + 1; k <= p; k++) {
						g[k] = lookup(k - c, h[k]);
					}
					break;
				}
			}
		}
		if (j <= p) {
			c = j + 1;
			r = j - 1;
		}
		else {
			c = p + 1;
			if (h[p]) r += h[p] - 1;
		}
	}
}

int main() {
	n = 9;
	solve();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			assert (f[i] <= D(j) + W(j, i));
		}
		cout << f[i] << " \n"[i == n - 1];
	}
	return 0;
}
