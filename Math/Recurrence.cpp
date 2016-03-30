#include <bits/stdc++.h>
using namespace std;

const int MOD = (int) 1e9 + 7;
const int MAXN = 1010;
int n;
int a[MAXN][MAXN];
int c[MAXN];
int d[MAXN];
int x[MAXN << 1];
int fpow(int n, int k, int p = MOD) {
	int r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = (long long) r * n % p;
		n = (long long) n * n % p;
	}
	return r;
}
void gauss(int a[][MAXN], int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = (a[i][j] % MOD + MOD) % MOD;
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int dmax = 0, idx;
		for (int j = i; j < m; j++) {
			if (dmax < a[j][i]) {
				dmax = a[j][i];
				idx = j;
			}
		}
		if (dmax == 0) {
			return;
		}
		for (int j = i; j < m; j++) {
			swap(a[i][j], a[idx][j]);
		}
		for (int j = i + 1; j < n; j++) {
			for (int k = i + 1; k < m; k++) {
				a[j][k] = ((long long) a[j][k] * a[i][i] % MOD - (long long) a[j][i] * a[i][k] % MOD + MOD) % MOD;
			}
			a[j][i] = 0;
		}
	}
	for (int i = 0; i < n; i++) if (a[i][i]) {
		for (int j = i + 1; j < m; j++) {
			a[i][j] = (long long) a[i][j] * fpow(a[i][i], MOD - 2) % MOD;
		}
		a[i][i] = 1;
	}
}

int main() {
	srand(time(NULL));
	int k = 20;
	for (int i = 0; i < k; i++) {
		x[i] = rand() % MOD;
		c[i] = rand() % MOD;
	}
	for (int i = k; i < (k << 1); i++) {
		for (int j = 0; j < k; j++) {
			x[i] = (x[i] + (long long) c[k - j - 1] * x[i - j - 1]) % MOD;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			a[i][j] = x[i + j];
		}
		a[i][k] = x[i + k];
	}
	gauss(a, k, k + 1);
	for (int i = k - 1; i >= 0; i--) {
		int t = 0;
		for (int j = i + 1; j < k; j++) {
			t = (t + (long long) a[i][j] * c[j]) % MOD;
		}
		d[i] = (long long) (a[i][k] - t + MOD) * fpow(a[i][i], MOD - 2) % MOD;
	}
	for (int i = 0; i < k; i++) {
		if (c[i] - d[i]) {
			cout<<"Wrong!\n";
			return 0;
		}
	}
	cout<<"Correct!\n";
	return 0;
}
