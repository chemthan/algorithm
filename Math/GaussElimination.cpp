#include <bits/stdc++.h>
using namespace std;

//O(n^2m)
typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;
#define EPS 1e-9
VVT ModularGauss(VVT a) {
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n - 1; i++) {
		T dmax = 0; int idx;
		for (int j = i; j < n; j++) {
			if (dmax < fabs(a[j][i])) {
				dmax = fabs(a[j][i]);
				idx = j;
			}
		}
		if (dmax < EPS) return a;
		swap(a[i], a[idx]);
		for (int j = i + 1; j < n; j++) {
			for (int k = i + 1; k < m; k++) {
				a[j][k] = a[j][k] * a[i][i] - a[j][i] * a[i][k];
			}
			a[j][i] = 0;
		}
	}
	for (int i = 0; i < n; i++) if (a[i][i]) {
		for (int j = i + 1; j < m; j++) {
			a[i][j] = a[i][j] / a[i][i];
		}
		a[i][i] = 1;
	}
	return a;
}

int main() {
	srand(time(NULL));
	int n = 3, m = 4;
	vector<vector<T> > a(n, vector<T>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = rand();
		}
	}
	a = ModularGauss(a);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout<<fixed<<setprecision(9)<<a[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
