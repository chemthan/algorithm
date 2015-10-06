#include <bits/stdc++.h>
using namespace std;

long long mul(long long a, long long b, long long mod) {
	return a * b % mod;
}
long long pow(long long a, long long k, long long mod) {
	if (k == 0) return 1;
	if (k & 1) return a * pow(a, k - 1, mod) % mod;
	long long t = pow(a, k >> 1, mod);
	return mul(t, t, mod);
}
bool rabin(long long n) {
	if (n == 2) return true;
	if (n < 2 || !(n & 1)) return false;
	const long long p[3] = {3, 5, 7};
	long long a, d = n - 1, mx = 3;
	int i, r, s = 0;
	while (!(d & 1)) {++s; d >>= 1;}
	for (i = 0; i < mx; i++) {
		if (n == p[i]) return true;
		if (!(n % p[i])) return false;
		a = pow(p[i], d, n);
		if (a != 1) {
			for (r = 0; r < s && a != n - 1; r++) a = mul(a, a, n);
			if (r == s) return false;
		}
	}
	return true;
}

int main() {
	printf("%d", rabin(1000000007));
	return 0;
}
