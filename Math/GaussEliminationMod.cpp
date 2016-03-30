#include <bits/stdc++.h>
using namespace std;

//O(n^2m)
const int MOD = (int) 1e9 + 7;
const int MAXN = 110;
int n, m;
int a[MAXN][MAXN];
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
	n = 3; m = 4;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = rand() % MOD;
		}
	}
	gauss(a, n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout<<a[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
