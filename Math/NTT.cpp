#include <bits/stdc++.h>
using namespace std;

int add(int a, int b, int p = (int) 1e9 + 7) {return a + b - (a + b >= p) * p;}
int sub(int a, int b, int p = (int) 1e9 + 7) {return a - b + (a - b < 0) * p;}
int mul(int a, int b, int p = (int) 1e9 + 7) {return ((long long) a * b) % p;}
int fpow(int a, int k, int p = (int) 1e9 + 7) {int r = 1; while (k) {if (k & 1) r = mul(r, a, p); k >>= 1; a = mul(a, a, p);} return r;}
int inv(int a, int p = (int) 1e9 + 7) {return fpow(a, p - 2, p);}
const int PRIME[3] = {1004535809, 1007681537, 1012924417}; //2 ^ 20 * {958, 961, 966}
const int gen[3] = {3, 3, 5}; //primitive roots
const int MAXN = 1 << 20;
int fa[MAXN];
int fb[MAXN];
int fd[3][MAXN];
int prv[MAXN];
int nxt[MAXN];
int roots[MAXN];
void fft(int a[], int k, int w, int p) {
	for (int i = 0; i < (1 << k); i++) prv[i] = nxt[i] = roots[i] = 0;
	int high = -1;
	for (int i = 1; i < (1 << k); i++) {
		if (!(i & (i - 1))) high++;
		prv[i] = prv[i ^ (1 << high)];
		prv[i] |= (1 << (k - 1 - high));
	}
	for (int i = 0; i < (1 << k); i++) prv[i] = a[prv[i]];
	roots[0] = 1;
	for (int i = 1; i < (1 << k); i++) roots[i] = mul(roots[i - 1], w, p);
	for (int len = 1; len < (1 << k); len <<= 1) {
		int rstep = (1 << k) / (len << 1);
		for (int pdest = 0; pdest < (1 << k); ) {
			int p1 = pdest;
			for (int i = 0; i < len; i++) {
				int val = mul(roots[i * rstep], prv[p1 + len], p);
				nxt[pdest] = add(prv[p1], val, p);
				nxt[pdest + len] = sub(prv[p1], val, p);
				pdest++;
				p1++;
			}
			pdest += len;
		}
		for (int i = 0; i < (1 << k); i++) swap(prv[i], nxt[i]);
	}
	for (int i = 0; i < (1 << k); i++) a[i] = prv[i];
}
void multiply(int a[], int b[], int c[], int na, int nb, int mod = (int) 1e9 + 7) {
	int len = na + nb - 1;
	int k = 0; while ((1 << k) <= 2 * max(na, nb)) k++;
	for (int r = 0; r < 3; r++) {
		for (int i = 0; i < (1 << k); i++) fa[i] = fb[i] = 0;
		for (int i = 0; i < na; i++) fa[i] = a[i];
		for (int i = 0; i < nb; i++) fb[i] = b[i];
		int p = PRIME[r];
		int w = fpow(gen[r], (p - 1) / (1 << k), p);
		fft(fa, k, w, p);
		fft(fb, k, w, p);
		for (int i = 0; i < (1 << k); i++) fd[r][i] = mul(fa[i], fb[i], p);
		fft(fd[r], k, inv(w, p), p);
		int rem = inv(1 << k, p);
		for (int i = 0; i < (1 << k); i++) {
			fd[r][i] = mul(fd[r][i], rem, p);
		}
	}
	for (int i = 0; i < len; i++) {
		long long cur = (long long) mul(sub(fd[1][i], fd[0][i], PRIME[1]), inv(PRIME[0], PRIME[1]), PRIME[1]) * PRIME[0] + fd[0][i];
		long long cur2 = mul(sub(fd[2][i], cur % PRIME[2], PRIME[2]), inv(mul(PRIME[0], PRIME[1], PRIME[2]), PRIME[2]), PRIME[2]);
		cur2 = add(mul(cur2 % mod, mul(PRIME[0], PRIME[1], mod), mod), cur % mod, mod);
		c[i] = cur2;
	}
}

const int maxn = 1 << 19;
int a[maxn];
int b[maxn];
int c[maxn << 1];
int d[maxn << 1];

int main() {
	srand(time(NULL));
	int n = 1000, p = (int) 1e8 + 7;
	for (int i = 0; i < n; i++) a[i] = rand() * rand() % 1000000000;
	for (int i = 0; i < n; i++) b[i] = rand() * rand() % 1000000000;
	multiply(a, b, c, n, n, p);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i + j] = (d[i + j] + 1LL * a[i] * b[j]) % p;
		}
	}
	for (int i = 0; i < (n << 1) - 1; i++) {
		if (c[i] != d[i]) {
			printf("Wrong!");
			return 0;
		}
	}
	printf("Correct!");
	return 0;
}
