#include <bits/stdc++.h>
using namespace std;

//O((logn)^2)
#define T int
const int MAXX = 1010;
const int MAXY = 1010;
T fen[MAXX][MAXY];
void update(int x, int y, T val) {
	while (x < MAXX) {
		int y1 = y;
		while (y1 < MAXY) {
			fen[x][y1] += val;
			y1 += y1 & -y1;
		}
		x += x & -x;
	}
}
T query(int x, int y) {
	T res = 0;
	while (x) {
		int y1 = y;
		while (y1) {
			res += fen[x][y1];
			y1 -= y1 & -y1;
		}
		x -= x & -x;
	}
	return res;
}

int main() {
	update(1, 1, 1);
	update(1, 2, 1);
	update(2, 1, 1);
	update(3, 3, 1);
	cout<<query(2, 2)<<"\n";
	return 0;
}
