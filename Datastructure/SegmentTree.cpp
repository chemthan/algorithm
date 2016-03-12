#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int st[4 * MAXN];
int lz[4 * MAXN];
void updatelz(int node, int L, int R) {
	if (lz[node]) {
		st[node] += (R - L + 1) * lz[node];
		if (L < R) {
			lz[node << 1] += lz[node];
			lz[(node << 1) + 1] += lz[node];
		}
		lz[node] = 0;
	}
}
void update(int node, int l, int r, int L, int R, int x) {
	updatelz(node, L, R);
	if (l > R || r < L) return;
	if (l <= L && r >= R) {
		lz[node] = x;
		updatelz(node, L, R);
		return;
	}
	update(node << 1, l, r, L, (L + R) >> 1, x);
	update((node << 1) + 1, l, r, ((L + R) >> 1) + 1, R, x);
	st[node] = st[node << 1] + st[(node << 1) + 1];
}
int query(int node, int l, int r, int L, int R) {
	updatelz(node, L, R);
	if (l > R || r < L) return 0;
	if (l <= L && r >= R) return st[node];
	return query(node << 1, l, r, L, (L + R) >> 1) + query((node << 1) + 1, l, r, ((L + R) >> 1) + 1, R);
}

int main() {
	update(1, 0, 3, 0, 9, 3);
	update(1, 2, 3, 0, 9, 4);
	update(1, 3, 4, 0, 9, 5);
	cout<<query(1, 3, 3, 0, 9);
	return 0;
}
