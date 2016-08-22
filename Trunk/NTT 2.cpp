#include <bits/stdc++.h>
using namespace std;

const int P1 = 998244353, P2 = 995622913;
const long long M1 = 397550359381069386LL, M2 = 596324591238590904LL;
const long long MM = 993874950619660289LL;
const int MAXN = 1 << 18;
int E1, E2, F1, F2, I1, I2;
int A[MAXN << 1], B[MAXN << 1], C[MAXN << 1];
int X[MAXN], Y[MAXN];
long long mul(long long a, long long b, long long p) {
	a %= p; b %= p;
	long long r = 0;
	for (; b; b >>= 1) {
		if (b & 1) r = (r + a) % p;
		a = (a + a) % p;
	}
	return r;
}
long long fpow(long long n, long long k, int p) {
	long long r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = r * n % p;
		n = n * n % p;
	}
	return r;
}
int CRT(int x1, int x2, int p) {
	return (mul(M1, x1, MM) + mul(M2, x2, MM)) % MM % p;
}
void NTT(int *A, int PM, int PW, int n) {
	for (int m = n, h; h = m / 2, m >= 2; PW = 1LL * PW * PW % PM, m = h) {
		for (int i = 0, w = 1; i < h; i++, w = 1LL * w * PW % PM) {
			for (int j = i; j < n; j += m) {
				int k = j + h, x = (A[j] - A[k] + PM) % PM;
				A[j] += A[k];
				A[j] %= PM;
				A[k] = 1LL * w * x % PM;
			}
		}
	}
	for (int i = 0, j = 1; j < n - 1; j++) {
		for (int k = n / 2; k > (i ^= k); k /= 2);
		if (j < i) swap(A[i], A[j]);
	}
}
int init(int n) {
	int k = 1, N = 2, p;
	while (N < n) {N <<= 1; k++;}
	assert(k <= 19);
	p = 7 * 17;
	for (int i = 1; i <= 23 - k; i++) p *= 2;
	E1 = fpow(3, p, P1);
	F1 = fpow(E1, P1 - 2, P1);
	I1 = fpow(N, P1 - 2, P1);
	p = 9 * 211;
	for (int i = 1; i <= 19 - k; i++) p *= 2;
	E2 = fpow(5, p, P2);
	F2 = fpow(E2, P2 - 2, P2);
	I2 = fpow(N, P2 - 2, P2);
	return N;
}
void mul(int* a, int* b, int* c, int n, int p) {
	int N = init(n);
	memcpy(X, a, sizeof(*a) * n); memcpy(Y, b, sizeof(*b) * n);
	memset(A, 0, sizeof(*A) * N); memset(B, 0, sizeof(*B) * N);
	memset(C, 0, sizeof(*C) * N); memset(c, 0, sizeof(*c) * N);
	memcpy(A, X, sizeof(*X) * n); memcpy(B, Y, sizeof(*Y) * n);
	NTT(A, P1, E1, N); NTT(B, P1, E1, N);
	for (int i = 0; i < N; i++) C[i] = (long long) A[i] * B[i] % P1;
	NTT(C, P1, F1, N);
	for (int i = 0; i < N; i++) C[i] = (long long) C[i] * I1 % P1;
	NTT(X, P2, E2, N); NTT(Y, P2, E2, N);
	for (int i = 0; i < N; i++) c[i] = (long long) X[i] * Y[i] % P2;
	NTT(c, P2, F2, N);
	for (int i = 0; i < N; i++) c[i] = (long long) c[i] * I2 % P2;
	for (int i = 0; i < N; i++) c[i] = CRT(C[i], c[i], p);
	for (int i = n; i < N; i++) c[i] = 0;
}

int a[MAXN];
int b[MAXN];
int c[MAXN << 1];
int d[MAXN << 1];

int main() {
	srand(time(NULL));
	int n = 1000, p = (int) 1e8 + 7;
	for (int i = 0; i < n; i++) a[i] = rand() * rand() % 10000;
	for (int i = 0; i < n; i++) b[i] = rand() * rand() % 10000;
	mul(a, b, c, n << 1, p);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i + j] = (d[i + j] + 1LL * a[i] * b[j]) % p;
		}
	}
	for (int i = 0; i < (n << 1) - 1; i++) {
		if (c[i] != d[i]) {
			cout << "Wrong!\n";
			return 0;
		}
	}
	cout << "Correct!\n";
	return 0;
}
