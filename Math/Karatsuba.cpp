#include <bits/stdc++.h>
using namespace std;

vector<long long> karatsuba(vector<long long>& a, vector<long long>& b) {
	while (a.size() & (a.size() - 1)) {a.push_back(0); b.push_back(0);}
	int n = a.size();
	vector<long long> res(n + n);
	if (n <= 32) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				res[i + j] += a[i] * b[j];
		return res;
	}
	int k = n >> 1;
	vector<long long> a1(a.begin(), a.begin() + k);
	vector<long long> a2(a.begin() + k, a.end());
	vector<long long> b1(b.begin(), b.begin() + k);
	vector<long long> b2(b.begin() + k, b.end());
	vector<long long> a1b1 = karatsuba(a1, b1);
	vector<long long> a2b2 = karatsuba(a2, b2);
	for (int i = 0; i < k; i++) a2[i] += a1[i];
	for (int i = 0; i < k; i++) b2[i] += b1[i];
	vector<long long> r = karatsuba(a2, b2);
	for (int i = 0; i < a1b1.size(); i++) r[i] -= a1b1[i];
	for (int i = 0; i < a2b2.size(); i++) r[i] -= a2b2[i];
	for (int i = 0; i < r.size(); i++) res[i + k] += r[i];
	for (int i = 0; i < a1b1.size(); i++) res[i] += a1b1[i];
	for (int i = 0; i < a2b2.size(); i++) res[i + n] += a2b2[i];
	return res;
}

long long d[100010];

int main() {
	srand(time(NULL));
	vector<long long> a, b;
	int n = 1000;
	for (int i = 0; i < n; i++) a.push_back(rand() * rand() % 10000);
	for (int i = 0; i < n; i++) b.push_back(rand() * rand() % 10000);
	vector<long long> c = karatsuba(a, b);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i + j] += a[i] * b[j];
		}
	}
	for (int i = 0; i < c.size(); i++) {
		if (c[i] != d[i]) {
			printf("Wrong!");
			return 0;
		}
	}
	printf("Correct!");
	return 0;
}
