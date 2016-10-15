#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(n^3)
*/
int fpow(int n, int k, int p) {
	int r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = (long long) r * n % p;
		n = (long long) n * n % p;
	}
	return r;
}
int inv(int n, int p) {
	return fpow(n, p - 2, p);
}
int MatrixDeterminant(vector<vector<int> > a, vector<int>& r, int mod) {
	int i, j, k, n = a.size(), m = a[0].size();
	int res = 1;
	for (i = 0; i < n; i++) {
		if (!a[i][i]) {
			for (j = i + 1; j < n; j++) {
				if (a[j][i]) {
					for (k = 0; k < m; k++) {
						a[i][k] = a[i][k] + a[j][k];
						if (a[i][k] >= mod) a[i][k] -= mod;
					}
					break;
				}
			}
			if (j == n) return 0;
		}
		int tmp = a[i][i], itmp = inv(tmp, mod);
		for (k = 0; k < m; k++) a[i][k] = (long long) a[i][k] * itmp % mod;
		res = (long long) res * tmp % mod;
		for (j = 0; j < n; j++) {
			if (j == i) continue;
			tmp = a[j][i];
			for (k = 0; k < m; k++) {
				a[j][k] -= (long long) a[i][k] * tmp % mod;
				if (a[j][k] < 0) a[j][k] += mod;
			}
		}
	}
	r.clear();
	for (int i = 0; i < n; i++) {
		r.push_back(a[i][n]);
	}
	return res;
}

int main() {
	srand(time(NULL));
	int n = 5, mod = (int) 1e9 + 7;
	vector<vector<int> > a(n, vector<int>(n + 1, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			a[i][j] = rand() % mod;
		}
	}
	vector<int> r;
	int det = MatrixDeterminant(a, r, mod);
	for (int i = 0; i < n; i++) {
		int t = 0;
		for (int j = 0; j < n; j++) {
			t = (t + (long long) a[i][j] * r[j]) % mod;
		}
		assert(t == a[i][n]);
	}
	cout << "Determinant: " << det << "\n";
	cout << "Solution: ";
	for (int i = 0; i < n; i++) {
		cout << r[i] << " ";
	}
	cout << "\n";
	return 0;
}
