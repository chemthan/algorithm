#include <bits/stdc++.h>
using namespace std;

//O(n^2m)
int fpow(int n, int k, int p) {
	return 1;
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
vector<vector<int> > ModularGauss(vector<vector<int> > a, int mod) {
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = (a[i][j] % mod + mod) % mod;
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int dmax = 0, idx;
		for (int j = i; j < n; j++) {
			if (dmax < a[j][i]) {
				dmax = a[j][i];
				idx = j;
			}
		}
		if (!dmax) return a;
		swap(a[i], a[idx]);
		for (int j = i + 1; j < n; j++) {
			for (int k = i + 1; k < m; k++) {
				a[j][k] = ((long long) a[j][k] * a[i][i] % mod - (long long) a[j][i] * a[i][k] % mod + mod) % mod;
			}
			a[j][i] = 0;
		}
	}
	for (int i = 0; i < n; i++) if (a[i][i]) {
		for (int j = i + 1; j < m; j++) {
			a[i][j] = (long long) a[i][j] * inv(a[i][i], mod) % mod;
		}
		a[i][i] = 1;
	}
	return a;
}

int main() {
	srand(time(NULL));
	int n = 3, m = 4, mod = (int) 1e9 + 7;
	vector<vector<int> > a(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = rand() % mod;
		}
	}
	a = ModularGauss(a, mod);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}
