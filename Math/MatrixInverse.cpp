#include <bits/stdc++.h>
using namespace std;


typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

inline int eq(T a, T b) {
	static const T EPS = 1e-9;
	return fabs(a - b) < EPS;
}
VVT MatrixInverse(VVT a) {
	int i, j, k, n = a.size();
	VVT res;
	res.resize(n);
	for (i = 0; i < n; i++) {
		res[i].resize(n);
		for (j = 0; j < n; j++) res[i][j] = 0;
		res[i][i] = 1;
	}
	for (i = 0; i < n; i++) {
		if (eq(a[i][i], 0)) {
			for (j = i + 1; j < n; j++) {
				if (!eq(a[j][i], 0)) {
					for (k = 0; k < n; k++) {
						a[i][k] += a[j][k];
						res[i][k] += res[j][k];
					}
					break;
				}
			}
			if (j == n) {
				res.clear();
				return res;
			}
		}
		T tmp = a[i][i];
		for (k = 0; k < n; k++) {
			a[i][k] /= tmp;
			res[i][k] /= tmp;
		}
		for (j = 0; j < n; j++) {
			if (j == i) continue;
			tmp = a[j][i];
			for (k = 0; k < n; k++) {
				a[j][k] -= a[i][k] * tmp;
				res[j][k] -= res[i][k] * tmp;
			}
		}
	}
	return res;
}

int main() {
	srand(time(NULL));
	int n = 100;
	VVT a(n, VT(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = rand();
		}
	}
	VVT ia = MatrixInverse(a);
	VVT b(n, VT(n, 0));
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			for (int j = 0; j < n; j++) {
				b[i][j] += a[i][k] * ia[k][j];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (!eq(b[i][i], 1)) {
			cout<<"Wrong!\n";
			return 0;
		}
		for (int j = 0; j < n; j++) {
			if (i != j && !eq(b[i][j], 0)) {
				cout<<"Wrong!\n";
				return 0;
			}
		}
	}
	cout<<"Correct!\n";
	return 0;
}
