#include <bits/stdc++.h>
using namespace std;

template<class T, class cmp = less<T> > struct RMQ {
	static const int MAXN = 100000 + 10;
	static const int LOGN = 20;
	int n;
	T a[MAXN];
	T f[LOGN][MAXN];

	T best(T a, T b) {
		if (cmp()(a, b)) return a;
		return b;
	}
	void build() {
		for (int i = 0; i < n; i++) f[0][i] = a[i];
		for (int l = 0, k; (k = 1 << l) < n; l++) {
			for (int i = 0; i + k < n; i++) {
				f[l + 1][i] = best(f[l][i], f[l][i + k]);
			}
		}
	}
	T query(int a, int b) {
		int l = a == b ? 0 : __lg(b - a);
		return best(f[l][a], f[l][b - (1 << l) + 1]);
	}
};

RMQ<int> rmq;

int main() {
	srand(time(NULL));
	for (int it = 0; it < 10; it++) {
		rmq.n = rand() % 100000 + 1;
		for (int i = 0; i < rmq.n; i++) {
			rmq.a[i] = rand();
		}
		rmq.build();
		for (int test = 0; test < 1000; test++) {
			int l = rand() % rmq.n, r = rand() % rmq.n;
			if (l > r) swap(l, r);
			int res = (int) 1e9;
			for (int i = l; i <= r; i++) {
				res = min(res, rmq.a[i]);
			}
			assert(rmq.query(l, r) == res);
		}
	}
	cout << "Correct!\n";
	cout << "Correct!\n";
	return 0;
}
