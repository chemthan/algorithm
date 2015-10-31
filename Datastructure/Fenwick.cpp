#include <bits/stdc++.h>
using namespace std;

//O(nlogn)
const int MAXN = 100010;
int fen[MAXN];
void add(int p, int val) {
	for (; p < MAXN; p += p & -p) fen[p] += val;
}
int get(int p) {
	int res = 0;
	for (; p > 0; p -= p & -p) res += fen[p];
	return res;
}

int main() {
	add(1, 1);
	add(2, 3);
	printf("%d", get(2));
	return 0;
}
