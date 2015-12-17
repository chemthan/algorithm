#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const long double PI = 2 * acos((long double) 0);
typedef complex<long double> cplex;
int rev[MAXN << 2];
cplex wlen_pw[MAXN << 2], fa[MAXN << 2], fb[MAXN << 2];
void fft(cplex a[], int n, bool invert) {
	for (int i = 0; i < n; i++) if (i < rev[i]) swap (a[i], a[rev[i]]);
	for (int len = 2; len <= n; len <<= 1) {
		long double alpha = 2 * PI / len * (invert ? -1 : +1);
		int len2 = len >> 1; wlen_pw[0] = cplex(1, 0);
		cplex wlen(cos(alpha), sin(alpha));
		for (int i = 1; i < len2; i++) wlen_pw[i] = wlen_pw[i - 1] * wlen;
		for (int i = 0; i < n; i += len) {
			cplex t, *pu = a + i, *pv = a + i + len2, *pu_end = a + i + len2, *pw = wlen_pw;
			for (; pu != pu_end; pu++, pv++, pw++) {t = *pv **pw; *pv = *pu - t; *pu += t;}
		}
	}
	if (invert) for (int i = 0; i < n; i++) a[i] /= n;
}
void calcRev(int n, int logn) {
	for (int i = 0; i < n; i++) {
		rev[i] = 0;
		for (int j = 0; j < logn; j++) if (i & (1 << j)) rev[i] |= 1 << (logn - 1 - j);
	}
}
void mulpoly(int a[], int b[], long long c[], int na, int nb, int& n) {
	int l = max(na, nb), logn = 0;
	for (n = 1; n < l; n <<= 1) logn++;
	n <<= 1; logn++; calcRev(n, logn);
	for (int i = 0; i < n; i++) fa[i] = fb[i] = cplex(0);
	for (int i = 0; i < na; i++) fa[i] = cplex(a[i]);
	for (int i = 0; i < nb; i++) fb[i] = cplex(b[i]);
	fft(fa, n, 0); fft(fb, n, 0);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, n, 1);
	for (int i = 0; i < n; i++) c[i] = (long long) (fa[i].real() + 0.5);
}

int a[MAXN];
int b[MAXN];
long long c[MAXN << 2];
long long d[MAXN << 2];

int main() {
	srand(time(NULL));
	int n, na = 10000, nb = 10000;
	for (int i = 0; i < na; i++) a[i] = rand() * rand() % 10000;
	for (int i = 0; i < nb; i++) b[i] = rand() * rand() % 10000;
	mulpoly(a, b, c, na, nb, n);
	for (int i = 0; i < na; i++) {
		for (int j = 0; j < nb; j++) {
			d[i + j] += a[i] * b[j];
		}
	}
	for (int i = 0; i < na + nb - 1; i++) {
		if (c[i] != d[i]) {
			printf("Wrong!");
			return 0;
		}
	}
	printf("Correct!");
	return 0;
}
