#include <bits/stdc++.h>
using namespace std;

template<class T> T mulmod(T a, T b, T p) {
	a %= p; b %= p;
	T q = (T) ((long double) a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
    /*
	T r = 0;
	int block = 1;
	T base = 1LL << block;
	for (; b; b >>= block) {
		r = (r + a * (b & (base - 1))) % p;
		a = a * base % p;
	}
	return r;
	*/
}
template<class T> T powmod(T n, T k, T p) {
	if (!n) return 0;
	T r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = mulmod(r, n, p);
		n = mulmod(n, n, p);
	}
	return r;
}

int main() {
	long long a = (long long) 1e15 + 2311;
	long long b = (long long) 1e16 + 1992;
	long long p = (long long) 1e18 + 2016;
	cout << mulmod(a, b, p) << "\n"; //Expect 81840000004553112
	cout << powmod(a, b, p) << "\n"; //Expect 457363391775234913
	return 0;
}
