#include <bits/stdc++.h>
using namespace std;

long long fpow(long long n, long long k, int p = (int) 1e9 + 7) {
	long long r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = r * n % p;
		n = n * n % p;
	}
	return r;
}
void XORFFT(int a[], int n, int p, int invert) {
	for (int i = 1; i < n; i <<= 1) {
		for (int j = 0; j < n; j += i << 1) {
			for (int k = 0; k < i; k++) {
				int u = a[j + k], v = a[i + j + k];
				a[j + k] = u + v;
				if (a[j + k] >= p) a[j + k] -= p;
				a[i + j + k] = u - v;
				if (a[i + j + k] < 0) a[i + j + k] += p;
			}
		}
	}
	if (invert) {
		long long inv = fpow(n, p - 2, p);
		for (int i = 0; i < n; i++) a[i] = a[i] * inv % p;
	}
}

const int maxn = 100000 + 10;
int n, p;
int a[maxn];
int b[maxn];
int c[maxn];

int main() {
	srand(time(NULL));
	n = 1 << 10;
	p = (int) 1e8 + 7;
	for (int i = 0; i < n; i++) a[i] = rand() * rand() % 10000;
	for (int i = 0; i < n; i++) b[i] = rand() * rand() % 10000;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i ^ j] = (c[i ^ j] + (long long) a[i] * b[j]) % p;
		}
	}
	XORFFT(a, n, p, 0);
	XORFFT(b, n, p, 0);
	for (int i = 0; i < n; i++) a[i] = (long long) a[i] * b[i] % p;
	XORFFT(a, n, p, 1);
	for (int i = 0; i < n; i++) {
		if (a[i] != c[i]) {
			cout << "Wrong!\n";
			return 0;
		}
	}
	cout << "Correct!\n";
	return 0;
}
