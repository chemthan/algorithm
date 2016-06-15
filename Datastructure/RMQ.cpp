#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXE = 20;
int n;
int a[MAXN];
int f[MAXN][MAXE];
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

int random(int k) {
	return abs(rand() * rand()) % k;
}

int main() {
	srand(time(NULL));
	n = random(50000) + 50000;
	for (int i = 0; i < n; i++) {
		a[i] = random((int) 1e9) - (int) 1e9;
	}
	build();
	for (int test = 0; test < 1000; test++) {
		int l = random(n), r = random(n);
		if (l > r) swap(l, r);
		int res = a[l];
		for (int i = l + 1; i <= r; i++) {
			res = min(res, a[i]);
		}
		assert(res == query(l, r));
	}
	cout<<"Correct!\n";
	return 0;
}
