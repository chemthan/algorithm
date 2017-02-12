#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N^2M)
*/
typedef double T;
typedef vector<T> ROW;
typedef vector<ROW> MATRIX;
#define EPS 1e-9

inline int sign(T x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(T x, T y) {return sign(x - y);}
MATRIX gauss(MATRIX a) {
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n - 1; i++) {
		pair<T, int> best;
		for (int j = i; j < n; j++) {
			best = max(best, make_pair(fabs(a[j][i]), j));
		}
		if (!sign(best.first)) continue;
		int idx = best.second;
		swap(a[i], a[idx]);
		for (int j = i + 1; j < n; j++) {
			for (int k = i + 1; k < m; k++) {
				a[j][k] = a[j][k] * a[i][i] - a[j][i] * a[i][k];
			}
			a[j][i] = 0;
		}
	}
	for (int i = 0; i < n; i++) if (sign(a[i][i])) {
		for (int j = i + 1; j < m; j++) {
			a[i][j] = a[i][j] / a[i][i];
		}
		a[i][i] = 1;
	}
	return a;
}

int main() {
	srand(time(NULL));
	int n = 5, m = 5;
	MATRIX a(n, ROW(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = rand() % 10;
		}
	}
	a = gauss(a);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << fixed << setprecision(3) << a[i][j] << " \n"[j == m - 1];
		}
	}
	return 0;
}
