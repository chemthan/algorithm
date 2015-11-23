#include <bits/stdc++.h>
using namespace std;

//Chinese Remainder theorem
//Return -1 if there is no solution
const int MAXN = 100010;
long long p[MAXN], r[MAXN], b[MAXN], x[MAXN];
pair<long long, long long> euclid(long long a, long long b) {
	if (b == 0) return make_pair(1, 0);
	pair <long long, long long> r = euclid(b, a % b);
	return make_pair(r.second, r.first - a / b * r.second);
} //a, b non-negative
long long chineseRemainder(int n, int p[], int r[]) {
	long long M = 1;
	for (int i = 0; i < n; i++) M *= p[i];
	long long N = 0;
	for (int i = 0; i < n; i++) {
		b[i] = M / p[i];
		x[i] = euclid(b[i], p[i]).first;
		N += r[i] * b[i] * x[i];
	}
	while (N - M >= 0) N -= M;
	while (N < 0) N += M;
	return N;
}

int main() {
	int p[] = {2, 3, 5};
	int r[] = {1, 2, 3};
	printf("%lld", chineseRemainder(3, p, r));
	return 0;
}
