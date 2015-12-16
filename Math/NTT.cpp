#include <bits/stdc++.h>
using namespace std;

const int D=23,C=7*17,mod=C*(1<<D)+1,G=3,N=262200;

long long exp(long long n, long long k, int p = (int) 1e9 + 7) {
	if (!k) return 1;
	if (k & 1) return n * exp(n, k - 1, p) % p;
	long long t = exp(n, k >> 1, p);
	return t * t % p;
}

int n,l;
long long g;
void setl(int len) {
	for (l = 0; (1 << l) < 2 * len; l++);
	n = 1 << l;
	g = exp(G, C * (1 << (D - l)));
}
int rebit(int x) {
	int y = 0;
	for (int i = 0; i < l; i++) if (x & (1 << i)) y |= 1 << (l - i - 1);
	return y;
}
void inplace(long long* t, int invert) {
	for (int i = 0; i < n; i++) {
		if (i < rebit(i)) swap(t[i], t[rebit(i)]);
	}
	for (int i = 1; i <= l; i++) {
		int d = 1 << i;
		long long g1 = exp(!invert ? g : exp(g, n - 1) , 1 << (l - i));
		for (int j = 0; j < n; j += d) {
			long long w = 1;
			for (int k = j; k < j + d / 2; k++) {
				long long t1 = t[k], t2 = t[k + d / 2] * w % mod;
				t[k] = (t1 + t2) % mod;
				t[k + d / 2] = (t1 - t2 + mod) % mod;
				w = w * g1 % mod;
			}
		}
	}
	if (invert) {
		long long rn = exp(n, mod - 2);
		for (int i = 0; i < n; i++)
			t[i] = t[i] * rn % mod;
	}
}
void NTT(long long* a, long long* b, long long* c, int h) {
	inplace(a, 1);
	if (a != b) inplace(b, 1);
	if (a != c && b != c) inplace(c, 1);
	for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod * c[i] % mod;
	inplace(a, 0);
	for (int i = h; i < n; i++) a[i] = 0LL;
	fill(b, b + n, 0LL);
	fill(c, c + n, 0LL);
}

int main() {
	return 0;
}
