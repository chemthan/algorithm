#include <bits/stdc++.h>
using namespace std;

//O(n^3)
//Index from 1
#define MAXN 1010
#define INF 1000000000
struct Hungary {
	int nx, ny, cost[MAXN][MAXN], fx[MAXN], fy[MAXN], maty[MAXN], which[MAXN], dist[MAXN];
	bool used[MAXN];
	void init(int _nx, int _ny) {
		nx = _nx; ny = _ny; memset(fx, 0, sizeof(fx)); memset(fy, 0, sizeof(fy)); memset(maty, 0, sizeof(maty));
		for (int i = 0; i <= nx; i++) for (int j = 0; j <= ny; j++) cost[i][j] = INF;
	}
	void add(int x, int y, int c) {cost[x][y] = c;}
	int mincost() {
		for (int x = 1; x <= nx; x++) {
			int y0 = 0; maty[0] = x;
			for (int y = 0; y <= ny; y++) {dist[y] = INF + 1; used[y] = false;}
			do {
				used[y0] = true;
				int x0 = maty[y0], delta = INF + 1, y1;
				for (int y = 1; y <= ny; y++) if (!used[y]) {
					int curdist = cost[x0][y] - fx[x0] - fy[y];
					if (curdist < dist[y]) {
						dist[y] = curdist;
						which[y] = y0;
					}
					if (dist[y] < delta) {
						delta = dist[y];
						y1 = y;
					}
				}
				for (int y = 0; y <= ny; y++) if (used[y]) {
					fx[maty[y]] += delta;
					fy[y] -= delta;
				}
				else dist[y] -= delta;
				y0 = y1;
			}
			while (maty[y0] != 0);
			do {
				int y1 = which[y0];
				maty[y0] = maty[y1];
				y0 = y1;
			}
			while (y0);
		}
		//return -fy[0]; //If ensure that always exist complete matching
		int ret = 0;
		for (int y = 1; y <= ny; y++) {
			int x = maty[y];
			if (cost[x][y] < INF) ret += cost[x][y];
		}
		return ret;
	}
} hungary;

int main() {
	hungary.init(3, 3);
	hungary.add(1, 2, 3);
	hungary.add(1, 2, 1);
	printf("%d", hungary.mincost());
	return 0;
}
