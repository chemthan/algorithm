#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N^3)
*/
#define EPS 1e-10
typedef double T;
typedef vector<T> ROW;
typedef vector<ROW> MATRIX;

inline int sign(T x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(T x, T y) {return sign(x - y);}
int rref(MATRIX& a) {
	int n = a.size(), m = a[0].size(), r = 0;
	for (int c = 0; c < m && r < n; c++) {
		int j = r;
		for (int i = r + 1; i < n; i++)
			if (fabs(a[i][c]) > fabs(a[j][c])) j = i;
		if (!sign(a[j][c])) continue;
		swap(a[j], a[r]);
		T s = 1.0 / a[r][c];
		for (int j = 0; j < m; j++) a[r][j] *= s;
		for (int i = 0; i < n; i++) if (i != r) {
			T t = a[i][c];
			for (int j = 0; j < m; j++) a[i][j] -= t * a[r][j];
		}
		r++;
	}
	return r;
}

int main() {
	int n = 5, m = 4;
	T A[n][m] = {
		{16,  2,  3, 13},
		{ 5, 11, 10,  8},
		{ 9,  7,  6, 12},
		{ 4, 14, 15,  1},
		{13, 21, 21, 13}
	};
	MATRIX a(n);
	for (int i = 0; i < n; i++) a[i] = ROW(A[i], A[i] + m);
	int rank = rref(a);
	//Expected: 3
	cout << "Rank: " << rank << "\n";
	/*Expected: 1 0 0 1
	            0 1 0 3
	            0 0 1 -3
	            0 0 0 3.10862e-15
	            0 0 0 2.22045e-15
	*/
	cout << "rref:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " \n"[j == m - 1];
		}
	}
}
