#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: Nlog(N)^2
* Solve dp formula: a[i] = a[i - 1] * b[0] + a[i - 2] * b[1] + ... + a[0] * b[i - 1]
* Problems:
* 1. http://codeforces.com/contest/553/problem/E
* 2. http://codeforces.com/gym/100959/status/H
* 3. https://www.bnuoj.com/v3/problem_show.php?pid=52248
*/
typedef long double T;
const int MAXN = 1 << 20;
struct cplex {
	T r, i;
	cplex() : r(0), i(0) {}
	cplex(T n) : r(n), i(0) {}
	cplex(T r, T i) : r(r), i(i) {}
	T real() {return r;}
	cplex operator + (cplex b) {return cplex (r + b.r, i + b.i);}
	void operator += (cplex b) {r += b.r, i += b.i;}
	cplex operator - (cplex b) {return cplex(r - b.r, i - b.i);}
	cplex operator * (cplex b) {return cplex(r * b.r - i * b.i, r * b.i + i * b.r);}
	cplex operator *= (cplex b) {T r2 = r * b.r - i * b.i, i2 = r * b.i + i * b.r; r = r2, i = i2;}
	void operator /= (T n) {r /= n, i /= n;}
};
void fft(cplex a[], int n, int invert) {
	static const T PI = 2 * acos((T) 0);
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
				cplex& x = a[i + j + m], &y = a[i + j], t = unit * x;
				x = y - t;
				y = y + t;
				unit *= w;
			}
		}
	}
	if (invert) for (int i = 0; i < n; i++) a[i] /= n;
}
void modularmultiply(int a[], int b[], int c[], int na, int nb, int mod = (int) 1e9 + 7) {
	static const int K = 2;
	static cplex ap[K][MAXN << 1], bp[K][MAXN << 1], cc[MAXN << 1];
	int n = 1; while (n < na + nb - 1) n <<= 1;
	int base = (int) pow(mod, 1.0 / K) + 1;
	for (int i = 0; i < n; i++) {
		int ta = i < na ? a[i] : 0, tb = i < nb ? b[i] : 0;
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

const int maxn = 1 << 20;
const int mod = (int) 1e9 + 7;
int n;
int a[maxn];
int b[maxn];
int c[maxn << 1];
int d[maxn];

int main() {
	srand(time(NULL));
	n = 1000;
	a[0] = d[0] = rand();
	for (int i = 0; i < n; i++) {
		b[i] = rand();
	}
	for (int i = 0; i < n; i++) {
		//a[i] has computed
		a[i + 1] = (a[i + 1] + (long long) a[i] * b[0]) % mod;
		a[i + 2] = (a[i + 2] + (long long) a[i] * b[1]) % mod;
		for (int k = 2; i && i % k == 0; k <<= 1) {
			modularmultiply(a + i - k, b + k, c, k, k, mod);
			for (int j = i + 1; j < i + 2 * k; j++) {
				a[j] = (a[j] + c[j - i - 1]) % mod;
			}
		}
		for (int j = 0; j < i; j++) {
			d[i] = (d[i] + (long long) d[j] * b[i - j - 1]) % mod;
		}
		cout << a[i] << " " << d[i] << "\n";
		assert(a[i] == d[i]);
	}
	cout << "Correct!\n";
	return 0;
}
