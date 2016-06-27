#include <bits/stdc++.h>
using namespace std;

typedef long long T;
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
    /*T q = T((long double) a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;*/
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

int main() {
	T a = (T) 1e15 + 2311;
	T b = (T) 1e16 + 1992;
	T p = (T) 1e18 + 2016;
	cout<<mulmod64(a, b, p)<<"\n"; //Expect 81840000004553112
	cout<<powmod64(a, b, p)<<"\n"; //Expect 457363391775234913
	return 0;
}
