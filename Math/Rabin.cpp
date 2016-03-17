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
//if n < 2,047, it is enough to test a = 2;
//if n < 1,373,653, it is enough to test a = 2 and 3;
//if n < 9,080,191, it is enough to test a = 31 and 73;
//if n < 25,326,001, it is enough to test a = 2, 3, and 5;
//if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7;
//if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
//if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
//if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
//if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
//if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
//if n < 3,825,123,056,546,413,051, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
//if n < 18,446,744,073,709,551,616 = 264, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
//if n < 318,665,857,834,031,151,167,461, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
//if n < 3,317,044,064,679,887,385,961,981, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, and 41.
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
