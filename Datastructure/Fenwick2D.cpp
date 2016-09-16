#include <bits/stdc++.h>
using namespace std;

//O((logN)^2)
#define T int
const int MAXX = 1000 + 10;
const int MAXY = 1000 + 10;
T fen[MAXX][MAXY];
void upd(int x, int y, T val) {
	for (; x < MAXX; x += x & -x) {
		for (int y1 = y; y1 < MAXY; y1 += y1 & -y1) {
			fen[x][y1] += val;
		}
	}
}
T query(int x, int y) {
	T res = 0;
	for (; x > 0; x -= x & -x) {
		for (int y1 = y; y1 > 0; y1 -= y1 & -y1) {
			res += fen[x][y1];
		}
	}
	return res;
}

int main() {
	upd(1, 1, 1);
	upd(1, 2, 1);
	upd(2, 1, 1);
	upd(3, 3, 1);
	cout << query(2, 2) << "\n";
	return 0;
}
