#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
struct HashModule {
	int h[MAXN], pw[MAXN], rp[MAXN], mod;
	int inv(int n) {
		int r = n, t = n, k = mod - 3;
		while (k) {
			if (k & 1) r = (long long) r * t % mod;
			t = (long long) t * t % mod;
			k >>= 1;
		}
		return r;
	}
	void init(string s, int base, int p) {
		mod = p;
		pw[0] = 1;
		for (int i = 1; i < MAXN; i++) {
			pw[i] = (long long) pw[i - 1] * base % mod;
		}
		rp[0] = 1; rp[1] = inv(base);
		for (int i = 1; i < MAXN; i++) {
			rp[i] = (long long) rp[i - 1] * rp[1] % mod;
		}
		for (int i = 0; i < s.size(); i++) {
			if (!i) {
				h[i] = s[i];
			}
			else {
				h[i] = h[i - 1] + (long long) s[i] * pw[i] % mod;
				if (h[i] >= mod) {
					h[i] -= mod;
				}
			}
		}
	}
	int query(int l, int r) {
		if (!l) return h[r];
		return (long long) (h[r] - h[l - 1] + mod) * rp[l] % mod;
	}
};
struct DoubleHash {
	HashModule hm1, hm2;
	void init(string s, int base1, int mod1, int base2, int mod2) {
		hm1.init(s, base1, mod1);
		hm2.init(s, base2, mod2);
	}
	pair<int, int> query(int l, int r) {
		return make_pair(hm1.query(l, r), hm2.query(l, r));
	}
};

DoubleHash dhash;

int main() {
	dhash.init("123456123456", 2311, (int) 1e9 + 7, 1992, (int) 1e8 + 7);
	pair<int, int> r = dhash.query(0, 3);
	cout<<r.first<<" "<<r.second<<"\n";
	r = dhash.query(6, 9);
	cout<<r.first<<" "<<r.second<<"\n";
	return 0;
}
