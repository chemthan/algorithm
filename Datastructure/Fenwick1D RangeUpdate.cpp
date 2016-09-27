#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(log(N))
*/
const int MAXN = 100000 + 10;
int fen[2][MAXN];
void upd(int p, int val) {
	for (int pp = p; pp < MAXN; pp += pp & -pp) {
		fen[0][pp] += val;
		fen[1][pp] += p * val;
	}
}
void upd(int l, int r, int val) {
	upd(l, +val), upd(r + 1, -val);
}
int query(int p) {
	int res = 0;
	for (int pp = p; pp > 0; pp -= pp & -pp) {
		res += (p + 1) * fen[0][pp];
		res -= fen[1][pp];
	}
	return res;
}

const int maxn = 100000 + 10;
int n;
int a[maxn];

int main() {
	srand(time(NULL));
	int n = 1000, q = 1000;
	while (q--) {
		if (rand() % 2 == 0) {
			int l = rand() % n, r = rand() % n, val = rand() % 1000;
			if (l > r) swap(l, r);
			upd(l + 1, r + 1, val);
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
			assert(ans == query(r + 1) - query(l));
			cout << ans << " " << query(r + 1) - query(l) << "\n";
		}
	}
	cout << "Correct!\n";
	return 0;
}
