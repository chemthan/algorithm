#include <bits/stdc++.h>
using namespace std;

//O(nlogn)
#define T int
const int MAXN = 100010;
int fen[MAXN];
void update(int p, T val) {
	for (; p < MAXN; p += p & -p) fen[p] += val;
}
T query(int p) {
	T res = 0;
	for (; p > 0; p -= p & -p) res += fen[p];
	return res;
}

int main() {
	update(1, 1);
	update(2, 3);
	printf("%d", query(2));
	return 0;
}
