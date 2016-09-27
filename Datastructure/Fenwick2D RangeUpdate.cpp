#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 10;
int fen[4][MAXN][MAXN];
void upd(int x, int y, int val) {
	for (int xx = x; xx < MAXN; xx += xx & -xx) {
		for (int yy = y; yy < MAXN; yy += yy & -yy) {
			fen[0][xx][yy] += val;
			fen[1][xx][yy] += x * val;
			fen[2][xx][yy] += y * val;
			fen[3][xx][yy] += x * y * val;
		}
	}
}
void upd(int x, int y, int z, int t, int val) {
	upd(x, y, +val);
	upd(x, t + 1, -val);
	upd(z + 1, y, -val);
	upd(z + 1, t + 1, +val);
}
int query(int x, int y) {
	int res = 0;
	for (int xx = x; xx > 0; xx -= xx & -xx) {
		for (int yy = y; yy > 0; yy -= yy & -yy) {
			res += (x + 1) * (y + 1) * fen[0][xx][yy];
			res -= (y + 1) * fen[1][xx][yy];
			res -= (x + 1) * fen[2][xx][yy];
			res += fen[3][xx][yy];
		}
	}
	return res;
}

const int maxn = 1000 + 10;
int a[maxn][maxn];

int main() {
	srand(time(NULL));
	int n = 1000, m = 1000, q = 1000;
	while (q--) {
		if (rand() % 2 == 0) {
			int x = rand() % n, y = rand() % m, z = rand() % n, t = rand() % m, val = rand() % 100;
			if (x > z) swap(x, z);
			if (y > t) swap(y, t);
			upd(x + 1, y + 1, z + 1, t + 1, val);
			for (int i = x; i <= z; i++) {
				for (int j = y; j <= t; j++) {
					a[i][j] += val;
				}
			}
		}
		else {
			int x = rand() % n, y = rand() % m, z = rand() % n, t = rand() % m;
			if (x > z) swap(x, z);
			if (y > t) swap(y, t);
			int ans = 0;
			for (int i = x; i <= z; i++) {
				for (int j = y; j <= t; j++) {
					ans += a[i][j];
				}
			}
			assert(ans == query(z + 1, t + 1) - query(x, t + 1) - query(z + 1, y) + query(x, y));
			cout << ans << " " << query(z + 1, t + 1) - query(x, t + 1) - query(z + 1, y) + query(x, y) << "\n";
		}
	}
	cout << "Correct!\n";
	return 0;
}
