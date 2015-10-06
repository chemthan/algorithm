#include <bits/stdc++.h>
using namespace std;

//Find x such that x * x = a [mod]
const int maxn = 100010;
long long qn[maxn];
long long ex(long long n, long long k, long long mod) {
	if (k == 0) return 1;
	if (k % 2 == 1) return n * ex(n, k - 1, mod) % mod;
	long long t = ex(n, k >> 1, mod);
	return t * t % mod;
}
long long calc(long long a, long long mod) {
	if (ex(a, (mod - 1) / 2, mod) != 1) return -1;
	if (mod % 4 == 3) return ex(a, (mod + 1) / 4, mod);
	long long q = mod - 1, s = 0;
	while (q % 2 == 0) {q /= 2; s++;}
	long long z = 1;
	if (qn[mod]) z = qn[mod];
	else {
		while (z++) {
			if (ex(z, (mod - 1) / 2, mod) == mod - 1)
				break;
		}
		qn[mod] = z;
	}
	long long c = ex(z, q, mod);
	long long r = ex(a, (q + 1) / 2, mod);
	long long t = ex(a, q, mod);
	long long m = s;
	while (1) {
		if (t == 1) return r;
		long long i = 1, tmp = t;
		while (i < m) {tmp = tmp * tmp % mod; if (tmp == 1) break; i++;}
		long long b = c, x = m - i - 1;
		while (x > 0) {b = b * b % mod; x--;}
		r = r * b % mod;
		t = t * b % mod * b % mod;
		c = b * b % mod;
		m = i;
	}
}

int main() {
	long long a = 2311, mod = 100000007;
	long long k = calc(a, mod);
	if (k == -1) {printf("-1"); return 0;}
	printf("%lld", k * k % mod);
	return 0;
}
