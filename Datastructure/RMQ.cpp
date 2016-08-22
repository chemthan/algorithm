#include <bits/stdc++.h>
using namespace std;

struct RMQ {
	static const int MAXN = 100000 + 10;
	static const int LOGN = 20;
	int n;
	int a[MAXN];
	int f[MAXN][LOGN];
	void build() {
		for (int i = 0; i < n; i++) f[i][0] = a[i];
		for (int l = 0, k; (k = 1 << l) < n; l++) {
			for (int i = 0; i + k < n; i++) {
				f[i][l + 1] = min(f[i][l], f[i + k][l]);
			}
		}
	}
	int query(int a, int b) {
		int l = a == b ? 0 : __lg(b - a);
		return min(f[a][l], f[b - (1 << l) + 1][l]);
	}
} rmq;

int random(int k) {
	return abs(rand() * rand()) % k;
}

int main() {
	srand(time(NULL));
	rmq.n = random(50000) + 50000;
	for (int i = 0; i < rmq.n; i++) {
		rmq.a[i] = random((int) 1e9) - (int) 1e9;
	}
	rmq.build();
	for (int test = 0; test < 1000; test++) {
		int l = random(rmq.n), r = random(rmq.n);
		if (l > r) swap(l, r);
		int res = rmq.a[l];
		for (int i = l + 1; i <= r; i++) {
			res = min(res, rmq.a[i]);
		}
		assert(res == rmq.query(l, r));
	}
	cout << "Correct!\n";
	return 0;
}
