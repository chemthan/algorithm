#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(Nlog(MOD), N)
*/
struct Interpolation {
	static const int MOD = (int) 1e9 + 7;
	static const int MAXN = 100000 + 5;
	int a[MAXN];
	int fac[MAXN];
	int ifac[MAXN];
	int prf[MAXN];
	int suf[MAXN];
	
	int fpow(int n, int k) {
		int r = 1;
		for (; k; k >>= 1) {
			if (k & 1) r = (long long) r * n % MOD;
			n = (long long) n * n % MOD;
		}
		return r;
	}
	void build() {
		fac[0] = ifac[0] = 1;
		for (int i = 1; i < MAXN; i++) {
			fac[i] = (long long) fac[i - 1] * i % MOD;
			ifac[i] = fpow(fac[i], MOD - 2);
		}
	}
	//Calculate P(x) of degree k - 1, k values at k distinct points are given
	int calc(int x, int k) {
		prf[0] = suf[k + 1] = 1;
		for (int i = 1; i <= k; i++) {
			prf[i] = (long long) prf[i - 1] * (x - i + MOD) % MOD;
		}
		for (int i = k; i >= 1; i--) {
			suf[i] = (long long) suf[i + 1] * (x - i + MOD) % MOD;
		}
		int res = 0;
		for (int i = 1; i <= k; i++) {
			if (!((k - i) & 1)) {
				res = (res + (long long) prf[i - 1] * suf[i + 1] % MOD * ifac[i - 1] % MOD * ifac[k - i] % MOD * a[i]) % MOD;
			}
			else {
				res = (res - (long long) prf[i - 1] * suf[i + 1] % MOD * ifac[i - 1] % MOD * ifac[k - i] % MOD * a[i] % MOD + MOD) % MOD;
			}
		}
		return res;
	}
} ip;

const int MOD = (int) 1e9 + 7;

int main() {
	ip.build();
	for (int i = 1; i < ip.MAXN; i++) {
		ip.a[i] = ((long long) 3111 * i * i * i - (long long) 54 * i * i + 13 * i) % MOD;
	}
	assert(ip.calc(1234, 4) == ip.a[1234]);
	cout << "Correct!\n";
	return 0;
}
