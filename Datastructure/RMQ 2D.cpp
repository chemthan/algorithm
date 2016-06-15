#include <bits/stdc++.h>
using namespace std;

//Index from 1
const int MAXN = 1010;
const int MAXM = 1010;
const int LOGN = 10;
const int LOGM = 10;
int n, m;
int a[MAXN][MAXM];
int f[MAXN][MAXM][LOGM];
int g[MAXM][LOGM][MAXN][LOGN];

void build() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= m; i++) {
			f[k][i][0] = a[k][i];
		}
		for (int j = 1; 1 << j <= m; j++) {
			for (int i = 0; i + (1 << j) - 1 <= m; i++) {
				f[k][i][j] = max(f[k][i][j - 1], f[k][i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	for (int k = 1; k <= m; k++) {
		for (int l = 0; k + (1 << l) - 1 <= m; l++) {
			for (int i = 1; i <= n; i++) {
				g[k][l][i][0] = f[i][k][l];
			}
			for (int j = 1; 1 << j <= n; j++) {
				for (int i = 0; i + (1 << j) - 1 <= n; i++) {
					g[k][l][i][j] = max(g[k][l][i][j - 1], g[k][l][i + (1 << (j - 1))][j - 1]);
				}
			}
		}
	}
}
int query(int i, int j, int a, int b) {
	int lga = __lg(a);
	int lgb = __lg(b);
	int res = g[j][lgb][i][lga];
	res = max(res, g[j + b - (1 << (lgb))][lgb][i + a - (1 << (lga))][lga]);
	res = max(res, g[j][lgb][i + a - (1 << (lga))][lga]);
	res = max(res, g[j + b - (1 << (lgb))][lgb][i][lga]);
	return res;
}

int main() {
	srand(time(NULL));
	n = m = 100;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			a[i][j] = rand() * rand();
		}
	}
	build();
	int q = 100;
	while (q--) {
		int u = abs(rand()) % n + 1, v = abs(rand()) % m + 1;
		int x = abs(rand()) % n + 1, y = abs(rand()) % m + 1;
		if (u > x) swap(u, x);
		if (v > y) swap(v, y);
		int r1 = query(u, v, x - u + 1, y - v + 1);
		int r2 = (int) -1e9;
		for (int i = u; i <= x; i++) {
			for (int j = v; j <= y; j++) {
				r2 = max(r2, a[i][j]);
			}
		}
		assert(r1 == r2);
	}
	cout<<"Correct!\n";
	return 0;
}
