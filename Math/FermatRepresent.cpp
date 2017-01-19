#include <bits/stdc++.h>
using namespace std;

inline mult(long long a, long long b, long long p) {
	long long q = (long long) ((long double) a * b / p);
    long long r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
}
inline int fpow(int n, int k, int p) {
	int r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = mult(r, n, p);
		n = mult(n, n, p);
	}
	return r;
}
template<class T> inline T isqrt(T k) {
	T r = sqrt(k) + 1;
	while (r * r > k) r--;
	return r;
}

long long func(long long p) {
	srand(2311);
	while (1) {
		long long u = (long long) rand() * rand() % p;
		if (fpow(u, (p - 1) / 2, p) == p - 1) {
			long long res = fpow(u, (p - 1) / 4, p);
			return max(res, p - res);
		}
	}
}
pair<int, int> doit(long long p) {
	long long a = p, b = func(p);
	long long ip = isqrt(p);
	while (b > ip) {
		a %= b;
		swap(a, b);
	}
	return make_pair(b, isqrt(p - b * b));
}

int main() {
	pair<int, int> res = doit(613);
	cout << res.first << " " << res.second << "\n";
	cout << res.first * res.first + res.second * res.second << "\n";
	return 0;
}
