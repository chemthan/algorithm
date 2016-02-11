#include <bits/stdc++.h>
using namespace std;

typedef long double T;
const int MAXN = 1 << 20;
const T PI = 2 * acos((T) 0);
typedef complex<T> cplex;
cplex fa[MAXN << 1], fb[MAXN << 1];
void fft(cplex a[], int n, int invert) {
	for (int i = 1, j = 0; i < n; i++) {
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j) swap(a[i], a[j]);
	}
	for (int m = 1; m < n; m <<= 1) {
		T p = PI / m * (invert ? -1 : 1);
		cplex w = cplex(cos(p), sin(p));
		for (int i = 0; i < n; i += m << 1) {
			cplex unit = 1;
			for (int j = 0; j < m; j++) {
				cplex &x = a[i + j + m], &y = a[i + j], t = unit * x;
				x = y - t;
				y = y + t;
				unit *= w;
			}
		}
	}
	if (invert) for (int i = 0; i < n; i++) a[i] /= n;
}
void multiply(int a[], int b[], long long c[], int na, int nb) {
	int n = 1; while (n < na + nb) n <<= 1;
	for (int i = 0; i < n; i++) fa[i] = fb[i] = cplex(0);
	for (int i = 0; i < na; i++) fa[i] = cplex(a[i]);
	for (int i = 0; i < nb; i++) fb[i] = cplex(b[i]);
	fft(fa, n, 0); fft(fb, n, 0);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, n, 1);
	for (int i = 0; i < n; i++) c[i] = (long long) (fa[i].real() + 0.5);
}
const int K = 2;
cplex ap[K][MAXN << 1], bp[K][MAXN << 1], cc[MAXN << 1];
void multiply2(int a[], int b[], int c[], int na, int nb, int mod = (int) 1e9 + 7) {
	int n = 1; while (n < na + nb) n <<= 1;
	int base = (int) pow(mod, 1.0 / K) + 1;
	for (int i = 0; i < n; i++) {
		int ta = a[i], tb = b[i];
		for (int j = 0; j < K; j++) {
			ap[j][i] = ta % base;
			ta /= base;
			bp[j][i] = tb % base;
			tb /= base;
		}
	}
	for (int i = 0; i < K; i++) {
		fft(ap[i], n, 0);
		fft(bp[i], n, 0);
	}
	for (int i = 0; i < n; i++) c[i] = 0;
	for (int i = 0; i < K; i++) for (int j = 0; j < K; j++) {
		for (int k = 0; k < n; k++) cc[k] = ap[i][k] * bp[j][k];
		fft(cc, n, 1);
		for (int k = 0; k < n; k++) {
			long long z = (long long) (cc[k].real() + 0.5);
			z = (z % mod + mod) % mod;
			for (int l = 0; l < i + j; l++) z = z * base % mod;
			c[k] += z; if (c[k] >= mod) c[k] -= mod;
		}
	}
}

const int MOD = (int) 1e9 + 7;
int a[MAXN];
int b[MAXN];
int c[MAXN << 1];
long long d[MAXN << 1];

int main() {
	srand(time(NULL));
	int na = 10000, nb = 10000;
	for (int i = 0; i < na; i++) a[i] = rand() * rand() % 1000000000;
	for (int i = 0; i < nb; i++) b[i] = rand() * rand() % 1000000000;
	multiply2(a, b, c, na, nb);
	for (int i = 0; i < na; i++) {
		for (int j = 0; j < nb; j++) {
			d[i + j] += (long long) a[i] * b[j];
			d[i + j] %= MOD;
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
