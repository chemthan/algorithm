#include <bits/stdc++.h>
using namespace std;

template<class T> mulmod(T a, T b, T p) {
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
template<class T> powmod(T n, T k, T p) {
	if (!n) return 0;
	T r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = mulmod(r, n, p);
		n = mulmod(n, n, p);
	}
	return r;
}
template<class T> pair<T, T> euclid(T a, T b) {
	if (!b) return make_pair(1, 0);
	pair<T, T> r = euclid(b, a % b);
	return make_pair(r.second, r.first - a / b * r.second);
}

const int MAXN = 100000 + 5;
long long p[MAXN], r[MAXN], b[MAXN], x[MAXN];

long long chineseRemainder(int p[], int r[], int n) {
	long long M = 1;
	for (int i = 0; i < n; i++) M *= p[i];
	long long N = 0;
	for (int i = 0; i < n; i++) {
		b[i] = M / p[i];
		x[i] = (euclid(b[i], (long long) p[i]).first % p[i] + p[i]) % p[i];
		N += mulmod(r[i] * b[i], x[i], M);
		if (N >= M) N -= M;
	}
	return N;
}

int main() {
	int p[] = {2, 3, 5};
	int r[] = {1, 2, 3};
	cout << chineseRemainder(p, r, 3) << "\n"; //Expected 23
	return 0;
}
