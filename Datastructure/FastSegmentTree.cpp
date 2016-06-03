#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXE = 20;
int st[MAXN << 1];
int lz[MAXN << 1];
void apply(int p, int n, int val) {
	st[p] += val;
	if (p < n) lz[p] += val;
}
void pushup(int p) {
	while (p > 1) p >>= 1, st[p] = min(st[p << 1], st[p << 1 | 1]) + lz[p];
}
void pushdown(int p, int n) {
	for (int i = MAXE; i > 0; i--) {
		int q = p >> i;
		if (lz[q]) {
			apply(q << 1, n, lz[q]);
			apply(q << 1 | 1, n, lz[q]);
			lz[q] = 0;
		}
	}
}
void upd(int l, int r, int n, int val) {
	l += n, r += n + 1;
	int l0 = l, r0 = r;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) apply(l++, n, val);
		if (r & 1) apply(--r, n, val);
	}
	pushup(l0); pushup(r0 - 1);
}
int query(int l, int r, int n) {
	l += n, r += n + 1;
	pushdown(l, n), pushdown(r - 1, n);
	int res = (int) 1e9;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = min(res, st[l++]);
		if (r & 1) res = min(st[--r], res);
	}
	return res;
}

int main() {
	upd(0, 0, 5, 1);
	upd(1, 1, 5, 4);
	upd(2, 2, 5, 3);
	upd(3, 3, 5, 2);
	upd(4, 4, 5, 5);
	cout<<query(1, 3, 5)<<"\n";
	upd(3, 3, 5, 3);
	cout<<query(1, 3, 5)<<"\n";
	return 0;
}
