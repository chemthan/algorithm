#include <bits/stdc++.h>
using namespace std;

template<class T> vector<T> karatsuba(vector<T>& a, vector<T>& b) {
    while (a.size() & (a.size() - 1)) {
        a.push_back(0);
        b.push_back(0);
    }
    int n = a.size();
    vector<T> res(n + n);
    if (n <= 8) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res[i + j] += a[i] * b[j];
        return res;
    }
    int k = n >> 1;
    vector<T> a1(a.begin(), a.begin() + k);
    vector<T> a2(a.begin() + k, a.end());
    vector<T> b1(b.begin(), b.begin() + k);
    vector<T> b2(b.begin() + k, b.end());
    vector<T> a1b1 = karatsuba(a1, b1);
    vector<T> a2b2 = karatsuba(a2, b2);
    for (int i = 0; i < k; i++) a2[i] += a1[i];
    for (int i = 0; i < k; i++) b2[i] += b1[i];
    vector<T> r = karatsuba(a2, b2);
    for (int i = 0; i < a1b1.size(); i++) r[i] -= a1b1[i];
    for (int i = 0; i < a2b2.size(); i++) r[i] -= a2b2[i];
    for (int i = 0; i < r.size(); i++) res[i + k] += r[i];
    for (int i = 0; i < a1b1.size(); i++) res[i] += a1b1[i];
    for (int i = 0; i < a2b2.size(); i++) res[i + n] += a2b2[i];
    return res;
}

int pos;
int buf[1 << 20];
//Require n is a power of 2
void multiply(int n, int a[], int b[], int r[], int p = (int) 1e9 + 7) {
    if (n <= 8) {
        for (int i = 0; i < n + n; i++) {
            r[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                r[i + j] += (long long) a[i] * b[j] % p;
                if (r[i + j] >= p) r[i + j] -= p;
            }
        }
        return;
    }
    int s = n / 2;
    multiply(s, a, b, r);
    multiply(s, a + s, b + s, r + n);
    int* a2 = buf + pos; pos += s;
    int* b2 = buf + pos; pos += s;
    int* r2 = buf + pos; pos += n;
    for (int i = 0; i < s; i++) {
        a2[i] = a[i] + a[i + s];
        if (a2[i] >= p) a2[i] -= p;
    }
    for (int i = 0; i < s; i++) {
        b2[i] = b[i] + b[i + s];
        if (b2[i] >= p) b2[i] -= p;
    }
    multiply(s, a2, b2, r2);
    for (int i = 0; i < n; i++) {
        r2[i] = r2[i] - (r[i] + r[i + n]);
        if (r2[i] < 0) r2[i] += p;
        if (r2[i] < 0) r2[i] += p;
    }
    for (int i = 0; i < n; i++) {
        r[i + s] += r2[i];
        if (r[i + s] >= p) r[i + s] -= p;
    }
    pos -= s + s + n;
}

const int maxn = 1e5 + 5;
const int MOD = (int) 1e9 + 7;
int x[maxn];
int y[maxn];
int z[maxn];
int d[maxn];

int main() {
    srand(time(NULL));
    vector<long long> a, b;
    int n = 1 << 10;
    for (int i = 0; i < n; i++) {
        a.push_back(rand());
        x[i] = a.back();
    }
    for (int i = 0; i < n; i++) {
        b.push_back(rand());
        y[i] = b.back();
    }
    vector<long long> c = karatsuba(a, b);
    multiply(n, x, y, z, MOD);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i + j] += (long long) a[i] * b[j] % MOD;
            if (d[i + j] >= MOD) d[i + j] -= MOD;
        }
    }
    for (int i = 0; i < c.size(); i++) {
        assert(c[i] % MOD == d[i]);
    }
    for (int i = 0; i < c.size(); i++) {
        assert(z[i] == d[i]);
    }
    cout << "Correct!\n";
    return 0;
}
