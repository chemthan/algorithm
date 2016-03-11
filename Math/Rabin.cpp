#include <bits/stdc++.h>
using namespace std;

#define T long long
T mulmod64(T a, T b, T p) {
	a %= p; b %= p;
	T r = 0;
	int block = 1;
	T base = 1LL << block;
	for (; b; b >>= block) {
		r = (r + a * (b & (base - 1))) % p;
		a = a * base % p;
	}
	return r;
}
T powmod64(T n, T k, T p) {
	if (!n) return 0;
	T r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = mulmod64(r, n, p);
		n = mulmod64(n, n, p);
	}
	return r;
}
int rabin(T n) {
	if (n == 2) return 1;
	if (n < 2 || !(n & 1)) return 0;
	const T p[3] = {3, 5, 7};
	T a, d = n - 1, mx = 3;
	int i, r, s = 0;
	while (!(d & 1)) {++s; d >>= 1;}
	for (i = 0; i < mx; i++) {
		if (n == p[i]) return 1;
		if (!(n % p[i])) return 0;
		a = powmod64(p[i], d, n);
		if (a != 1) {
			for (r = 0; r < s && a != n - 1; r++) a = mulmod64(a, a, n);
			if (r == s) return 0;
		}
	}
	return 1;
}

int main() {
	cout<<rabin(1000000007)<<"\n";
	cout<<rabin(100000007)<<"\n";
	cout<<rabin(10000007)<<"\n";
	cout<<rabin(1000007)<<"\n";
	cout<<rabin(100007)<<"\n";
	cout<<rabin(10007)<<"\n";
	cout<<rabin(1007)<<"\n";
	cout<<rabin(107)<<"\n";
	cout<<rabin(17)<<"\n";
	return 0;
}
