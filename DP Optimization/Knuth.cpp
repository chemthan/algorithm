#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(NM)
* f[i][j] = f[i][k] + f[k][j] + c[i][j], i < k < j
* a[i][j] = min(k | i < k < j && f[i][j] = f[i][k] + f[k][j] + c[i][j]
* Sufficient condition: a[i][j - 1] <= a[i][j] <= a[i + 1][j] or
* c[a][c] + c[b][d] <= c[a][d] + c[b][c] (quadrangle inequality) and c[b][c] <= C[a][d] (monotonicity), a <= b <= c <= d
*/

const int oo = (int) 1e9;
const int MAXN = 1010;
const int MAXM = 1010;
int n;
int f[MAXN][MAXM];
int c[MAXN][MAXM];
int a[MAXN][MAXM];

void knuth() {
	for (int i = 0; i < n; i++) {
		f[i][i] = 0;
		a[i][i] = i;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			f[i][j] = oo;
			for (int k = a[i][j - 1]; k <= a[i + 1][j]; k++) {
				if (f[i][j] > f[i][k] + f[k][j] + c[i][j]) {
					f[i][j] = f[i][k] + f[k][j] + c[i][j];
					a[i][j] = k;
				}
			}
		}
	}
}

int main() {
	return 0;
}
