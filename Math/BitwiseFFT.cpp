#include <bits/stdc++.h>
using namespace std;

int fpow(int n, long long k, int p = (int) 1e9 + 7) {
    int r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = (long long) r * n % p;
        n = (long long) n * n % p;
    }
    return r;
}

/*
 * matrix:
 * +1 +1
 * +1 -1
 */
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
/*
 * Matrix:
 * +1 +1
 * +1 +0
 */
void ORFFT(int a[], int n, int p, int invert) {
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; k++) {
                int u = a[j + k], v = a[i + j + k];
                if (!invert) {
                    a[j + k] = u + v;
                    a[i + j + k] = u;
                    if (a[j + k] >= p) a[j + k] -= p;
                }
                else {
                    a[j + k] = v;
                    a[i + j + k] = u - v;
                    if (a[i + j + k] < 0) a[i + j + k] += p;
                }
            }
        }
    }
}
/*
 * matrix:
 * +0 +1
 * +1 +1
 */
void ANDFFT(int a[], int n, int p, int invert) {
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; k++) {
                int u = a[j + k], v = a[i + j + k];
                if (!invert) {
                    a[j + k] = v;
                    a[i + j + k] = u + v;
                    if (a[i + j + k] >= p) a[i + j + k] -= p;
                }
                else {
                    a[j + k] = v - u;
                    if (a[j + k] < 0) a[j + k] += p;
                    a[i + j + k] = u;
                }
            }
        }
    }
}

const int maxn = 1e5 + 5;
int n, p;
int a[maxn];
int b[maxn];
int c[maxn];

void testXOR() {
    fill_n(a, maxn, 0);
    fill_n(b, maxn, 0);
    fill_n(c, maxn, 0);
    for (int i = 0; i < n; i++) a[i] = (long long) rand() * rand() % 100000;
    for (int i = 0; i < n; i++) b[i] = (long long) rand() * rand() % 100000;
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
        cerr << a[i] << " " << c[i] << "\n";
        assert(a[i] == c[i]);
    }
}
void testOR() {
    fill_n(a, maxn, 0);
    fill_n(b, maxn, 0);
    fill_n(c, maxn, 0);
    for (int i = 0; i < n; i++) a[i] = (long long) rand() * rand() % 100000;
    for (int i = 0; i < n; i++) b[i] = (long long) rand() * rand() % 100000;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i | j] = (c[i | j] + (long long) a[i] * b[j]) % p;
        }
    }
    ORFFT(a, n, p, 0);
    ORFFT(b, n, p, 0);
    for (int i = 0; i < n; i++) a[i] = (long long) a[i] * b[i] % p;
    ORFFT(a, n, p, 1);
    for (int i = 0; i < n; i++) {
        cerr << a[i] << " " << c[i] << "\n";
        assert(a[i] == c[i]);
    }
}
void testAND() {
    fill_n(a, maxn, 0);
    fill_n(b, maxn, 0);
    fill_n(c, maxn, 0);
    for (int i = 0; i < n; i++) a[i] = (long long) rand() * rand() % 100000;
    for (int i = 0; i < n; i++) b[i] = (long long) rand() * rand() % 100000;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i & j] = (c[i & j] + (long long) a[i] * b[j]) % p;
        }
    }
    ANDFFT(a, n, p, 0);
    ANDFFT(b, n, p, 0);
    for (int i = 0; i < n; i++) a[i] = (long long) a[i] * b[i] % p;
    ANDFFT(a, n, p, 1);
    for (int i = 0; i < n; i++) {
        cerr << a[i] << " " << c[i] << "\n";
        assert(a[i] == c[i]);
    }
}

int main() {
    srand(time(0));
    n = 1 << 10, p = (int) 1e9 + 7;
    testXOR();
    testOR();
    testAND();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
