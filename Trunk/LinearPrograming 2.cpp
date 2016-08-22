#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9
const int MAXN = 1000 + 10;
const int MAXM = 1000 + 10;
double a[MAXN][MAXM], b[MAXN], c[MAXM], d[MAXN][MAXM];
int idx[MAXN + MAXM];
//Array all indexed from 0
//Maximize {cx | ax <= b, x >= 0}, n: constraints, m: vars
double simplex(double a[MAXN][MAXM], double b[MAXN], double c[MAXM], int n, int m) {
	m++; int r = n, s = m - 1;
	memset(d, 0, sizeof(d));
	for (int i = 0; i < n + m; i++) idx[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) d[i][j] = -a[i][j];
		d[i][m - 1] = 1;
		d[i][m] = b[i];
		if (d[r][m] > d[i][m]) r = i;
	}
	for (int j = 0; j < m - 1; j++) d[n][j] = c[j];
	d[n + 1][m - 1] = -1;
	while (1) {
		double dd;
		if (r < n) {
			int t = idx[s];
			idx[s] = idx[r + m];
			idx[r + m] = t;
			d[r][s] = 1.0 / d[r][s];
			for (int j = 0; j <= m; j++) if (j != s) d[r][j] *= -d[r][s];
			for (int i = 0; i <= n + 1; i++) {
				if (i != r) {
					for (int j = 0; j <= m; j++) if (j != s) d[i][j] += d[r][j] * d[i][s];
					d[i][s] *= d[r][s];
				}
			}
		}
		r = -1; s = -1;
		for (int j = 0; j < m; j++) {
			if (s < 0 || idx[s] > idx[j]) {
				if (d[n + 1][j] > EPS || (d[n + 1][j] > -EPS && d[n][j] > EPS)) s = j;
			}
		}
		if (s < 0) break;
		for (int i = 0; i < n; i++) {
			if (d[i][s] < -EPS) {
				if (r < 0 || (dd = d[r][m] / d[r][s] - d[i][m] / d[i][s]) < -EPS || (dd < EPS && idx[r + m] > idx[i + m])) r = i;
			}
		}
		if (r < 0) return -1; //Not bounded
	}
	if (d[n + 1][m] < -EPS) return -1; //Not executable
	double ans = 0;
	for (int i = m; i < n + m; i++) { //The missing enumerated x[i] = 0
		if (idx[i] < m - 1) ans += d[i - m][m] * c[idx[i]];
	}
	return ans;
}

int main() {
	int n = 3, m = 3;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = i * j + 6;
		}
	}
	for (int i = 0; i < n; i++) b[i] = i + 1;
	for (int i = 0; i < m; i++) c[i] = i * i + 1;
	cout << fixed << setprecision(9) << simplex(a, b, c, n, m) << "\n"; //Should be 0.833333333
	return 0;
}
