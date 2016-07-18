#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int LOGN = 20;
int st[MAXN << 1];
int sz[MAXN << 1];
int lz[MAXN];
void build(int n) {
	fill_n(sz + n, n, 1);
	for (int i = n - 1; i > 0; i--) {
		sz[i] = sz[i << 1] + sz[i << 1 | 1];
		st[i] = st[i << 1] + st[i << 1 | 1];
	}
}
void apply(int p, int n, int val) {
	st[p] += val * sz[p];
	if (p < n) lz[p] += val;
}
void pushup(int p) {
	while (p > 1) p >>= 1, st[p] = st[p << 1] + st[p << 1 | 1] + lz[p] * sz[p];
}
void pushdown(int p, int n) {
	for (int i = LOGN; i > 0; i--) {
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
	int res = 0;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += st[l++];
		if (r & 1) res += st[--r];
	}
	return res;
}

const int maxn = 100010;
int a[maxn];

int main() {
	srand(time(NULL));
	int n = 1000, q = 1000;
	for (int i = 0; i < n; i++) {
		a[i] = st[i + n] = rand() % 123;
	}
	build(n);
	while (q--) {
		int op = rand() & 1;
		if (op) {
			int l = rand() % n, r = rand() % n, val = rand() % 123;
			if (l > r) swap(l, r);
			upd(l, r, n, val);
			for (int i = l; i <= r; i++) {
				a[i] += val;
			}
		}
		else {
			int l = rand() % n, r = rand() % n;
			if (l > r) swap(l, r);
			int ans = 0;
			for (int i = l; i <= r; i++) {
				ans += a[i];
			}
			assert(ans == query(l, r, n));
		}
	}
	cout << "Correct!\n";
	return 0;
}
