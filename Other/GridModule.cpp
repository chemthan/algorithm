#include <bits/stdc++.h>
using namespace std;

#define T long long
struct GridModule {
	int n, m;
	vector<vector<int> > a;
	vector<vector<int> > sum;
	vector<vector<T> > row, col;
	vector<vector<T> > dig[2];
	void init(vector<vector<int> >& x) {
		a = x; n = a.size();
		if (n) m = a[0].size(); else m = 0;
		sum.resize(n);
		for (int i = 0; i < n; i++) {
			sum[i].clear();
			for (int j = 0; j < m; j++) {
				T t = a[i][j];
				if (i) {
					t += sum[i - 1][j];
				}
				if (j) {
					t += sum[i][j - 1];
				}
				if (i && j) {
					t -= sum[i - 1][j - 1];
				}
				sum[i].push_back(t);
			}
		}
		row.resize(n);
		for (int i = 0; i < n; i++) {
			row[i].clear();
			T tot = 0;
			for (int j = 0; j < m; j++) {
				tot += a[i][j];
				row[i].push_back(tot);
			}
		}
		col.resize(m);
		for (int j = 0; j < m; j++) {
			col[j].clear();
			T tot = 0;
			for (int i = 0; i < n; i++) {
				tot += a[i][j];
				col[j].push_back(tot);
			}
		}
		dig[0].resize(n + m - 1);
		for (int i = 0; i < m; i++) {
			dig[0][i].clear();
			T tot = 0;
			for (int j = 0; j < min(i + 1, n); j++) {
				tot += a[j][i - j];
				dig[0][i].push_back(tot);
			}
		}
		for (int i = 1; i < n; i++) {
			dig[0][i + m - 1].clear();
			T tot = 0;
			for (int j = 0; j < min(n - i, m); j++) {
				tot += a[i + j][m - j - 1];
				dig[0][i + m - 1].push_back(tot);
			}
		}
		dig[1].resize(n + m - 1);
		for (int i = m - 1; i >= 0; i--) {
			dig[1][m - i - 1].clear();
			T tot = 0;
			for (int j = 0; j < min(m - i, n); j++) {
				tot += a[j][i + j];
				dig[1][m - i - 1].push_back(tot);
			}
		}
		for (int i = 1; i < n; i++) {
			dig[1][i + m - 1].clear();
			T tot = 0;
			for (int j = 0; j < min(n - i, m); j++) {
				tot += a[i + j][j];
				dig[1][i + m - 1].push_back(tot);
			}
		}
	}
	T getsum(int x, int y, int z, int t) {
		if (x > z) {
			swap(x, z);
			swap(y, t);
		}
		T res = sum[z][t];
		if (x) {
			res -= sum[x - 1][t];
		}
		if (y) {
			res -= sum[z][y - 1];
		}
		if (x && y) {
			res += sum[x - 1][y - 1];
		}
		return res;
	}
	T rowsum(int x, int y, int z) {
		if (y > z) swap(y, z);
		return row[x][z] - (y ? row[x][y - 1] : 0);
	}
	T colsum(int x, int y, int z) {
		if (y > z) swap(y, z);
		return col[x][z] - (y ? col[x][y - 1] : 0);
	}
	T diagonal(int x, int y, int z, int t) {
		if (x > z) {
			swap(x, z);
			swap(y, t);
		}
		if (x + y == z + t) {
			int u = x + y;
			if (u >= m) {
				x = m - y - 1;
				z = m - t - 1;
			}
			return dig[0][u][z] - (x ? dig[0][u][x - 1] : 0);
		}
		else if (x - y == z - t) {
			int u = m + x - y - 1;
			if (u >= m) {
				x = y;
				z = t;
			}
			return dig[1][u][z] - (x ? dig[1][u][x - 1] : 0);
		}
		return 0;
	}
};

int main() {
	vector<vector<int> > a;
	a.resize(3);
	for (int i = 0; i < 3; i++) {
		a[i].resize(3);
	}
	a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
	a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
	a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;
	GridModule gm; gm.init(a);
	cout << gm.getsum(1, 0, 2, 1) << "\n"; //Expected 24
	cout << gm.rowsum(1, 1, 2) << "\n"; //Expected 11
	cout << gm.colsum(1, 0, 2) << "\n"; //Expected 15
	cout << gm.diagonal(0, 1, 1, 2) << "\n"; //Expected 8
	cout << gm.diagonal(0, 2, 2, 0) << "\n"; //Expected 15
	return 0;
}
