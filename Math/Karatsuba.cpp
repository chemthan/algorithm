#include <bits/stdc++.h>
using namespace std;

#define T long long
vector<T> karatsuba(vector<T>& a, vector<T>& b) {
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
T buf[1 << 20];
//Require n is a power of 2
void multiply(int n, T a[], T b[], T r[], T p = (T) 1e9 + 7) {
	if (n <= 8) {
		for (int i = 0; i < n + n; i++) {
			r[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				r[i + j] += a[i] * b[j];
				r[i + j] %= p;
			}
		}
		return;
	}
	int s = n / 2;
	multiply(s, a, b, r);
	multiply(s, a + s, b + s, r + n);
	T* a2 = buf + pos; pos += s;
	T* b2 = buf + pos; pos += s;
	T* r2 = buf + pos; pos += n;
	for (int i = 0; i < s; i++) {
		a2[i] = (a[i] + a[i + s]) % p;
	}
	for (int i = 0; i < s; i++) {
		b2[i] = (b[i] + b[i + s]) % p;
	}
	multiply(s, a2, b2, r2);
	for (int i = 0; i < n; i++) {
		r2[i] = (r2[i] - (r[i] + r[i + n]) % p + p) % p;
	}
	for (int i = 0; i < n; i++) {
		r[i + s] += r2[i];
		r[i + s] %= p;
	}
	pos -= s + s + n;
}

const int maxn = 100000 + 10;
const T MOD = (T) 1e9 + 7;
T x[maxn];
T y[maxn];
T z[maxn];
T d[maxn];

int main() {
	srand(time(NULL));
	vector<T> a, b;
	int n = 1 << 10;
	for (int i = 0; i < n; i++) {
		a.push_back(rand() * rand() % 1000000);
		x[i] = a.back();
	}
	for (int i = 0; i < n; i++) {
		b.push_back(rand() * rand() % 1000000);
		y[i] = b.back();
	}
	vector<T> c = karatsuba(a, b);
	multiply(n, x, y, z, MOD);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i + j] += a[i] * b[j];
		}
	}
	for (int i = 0; i < c.size(); i++) {
		if (c[i] != d[i]) {
			cout << "Wrong!\n";
			return 0;
		}
	}
	for (int i = 0; i < c.size(); i++) {
		if (z[i] != d[i] % MOD) {
			cout << "Wrong!\n";
			return 0;
		}
	}
	cout << "Correct!\n";
	return 0;
}
