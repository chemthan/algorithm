#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;
const int LOGN = 20;
int tr[LOGN + 1][MAXN];
int sm[LOGN + 1][MAXN];
void insert(int x, int t) {
	for (int i = 0; i < LOGN; i++) {
		tr[i][x]++;
		sm[i][x] += t;
		x >>= 1;
	}
}
void erase(int x, int t) {
	for (int i = 0; i < LOGN; i++) {
		tr[i][x]--;
		sm[i][x] -= t;
		x >>= 1;
	}
}
int kthelm(int k) {
	int res = 0;
	int a = 0, b = LOGN;
	while (b--) {
		a <<= 1;
		k -= tr[b][a] < k ? tr[b][a++] : 0;
		res = sm[b][a] / tr[b][a];
	}
	return res;
}
int kthsum(int k) {
	int res = 0;
	int a = 0, b = LOGN;
	while (b--) {
		a <<= 1;
		if (tr[b][a] < k) {
			res += sm[b][a];
		}
		k -= tr[b][a] < k ? tr[b][a++] : 0;
		if (!b) res += sm[b][a] / tr[b][a] * k;
	}
	return res;
}

int main() {
	insert(0, 0); insert(1, 1); insert(1, 1);
	insert(1, 1); insert(1, 1); insert(1, 1);
	insert(2, 2);
	cout << kthsum(7) << "\n";
	erase(2, 2);
	cout << kthsum(6) << "\n";
	return 0;
}
