#include <bits/stdc++.h>
using namespace std;

//O(nlog(mod), n)
const int MOD = (int) 1e9 + 7;
const int MAXN = 100010;
int a[MAXN];
int fac[MAXN];
int rfac[MAXN];
int pref[MAXN];
int suff[MAXN];

int fpow(int n, int k, int p = MOD) {
	int r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = (long long) r * n % p;
		n = (long long) n * n % p;
	}
	return r;
}
void build() {
	fac[0] = rfac[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fac[i] = (long long) fac[i - 1] * i % MOD;
		rfac[i] = fpow(fac[i], MOD - 2);
	}
}
int interpolation(int x, int k) {
	pref[0] = suff[k + 1] = 1;
	for (int i = 1; i <= k; i++) {
		pref[i] = (long long) pref[i - 1] * (x - i + MOD) % MOD;
	}
	for (int i = k; i >= 1; i--) {
		suff[i] = (long long) suff[i + 1] * (x - i + MOD) % MOD;
	}
	int res = 0;
	for (int i = 1; i <= k; i++) {
		if (!((k - i) & 1)) {
			res = (res + (long long) pref[i - 1] * suff[i + 1] % MOD * rfac[i - 1] % MOD * rfac[k - i] % MOD * a[i]) % MOD;
		}
		else {
			res = (res - (long long) pref[i - 1] * suff[i + 1] % MOD * rfac[i - 1] % MOD * rfac[k - i] % MOD * a[i] % MOD + MOD) % MOD;
		}
	}
	return res;
}

int main() {
	build();
	for (int i = 1; i < MAXN; i++) {
		a[i] = ((long long) 3111 * i * i * i - (long long) 54 * i * i + 13 * i) % MOD;
	}
	if (interpolation(1234, 4) == a[1234]) {
		cout<<"Correct!\n";
	}
	else {
		cout<<"Wrong!\n";
	}
	return 0;
}
